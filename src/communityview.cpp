#include "communityview.h"

#include "community.h"
#include "communitymodel.h"
#include "workperiod.h"
#include "workperioddialog.h"

#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>

Q_DECLARE_METATYPE(Community*);
Q_DECLARE_METATYPE(WorkPeriod*);

CommunityView::CommunityView(QWidget * parentWidget)
  : QTableView(parentWidget)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(handleContextMenu(QPoint)));
}

void CommunityView::addWorkPeriod()
{
  std::unique_ptr<WorkPeriod> workPeriod(new WorkPeriod);
  workPeriod->setStart(QDateTime(QDate::currentDate(), QTime::currentTime()));
  workPeriod->setEnd(QDateTime(QDate::currentDate(), QTime::currentTime()));
  int response = showWorkPeriodDialog(workPeriod.get());
  if (response == QDialog::Accepted) {
    QVariant v = model()->data(QModelIndex(), CommunityModel::CommunityRole);
    Community * community = v.value<Community*>();
    community->addWorkPeriod(std::move(workPeriod));
    update();
  }
}

void CommunityView::handleContextMenu(const QPoint & pt)
{
  QMenu popupMenu(this);
  QAction add("Add Work Period");
  QAction remove("Remove Work Period");
  QAction showProperties("Properties");

  WorkPeriod * workPeriod = nullptr;
  QModelIndex index = indexAt(pt);
  if (index.isValid()) {
    QVariant v = model()->data(index, CommunityModel::WorkPeriodRole);
    workPeriod = v.value<WorkPeriod*>();

    popupMenu.addAction(&add);
    popupMenu.addAction(&remove);
    popupMenu.addSeparator();
    popupMenu.addAction(&showProperties);
  }
  else {
    popupMenu.addAction(&add);
  }

  QAction * selectedAction = popupMenu.exec(viewport()->mapToGlobal(pt));
  if (selectedAction == &add) {
    addWorkPeriod();
  }
  else if (selectedAction == &remove) {
    removeWorkPeriod(workPeriod);
  }
  else if (selectedAction == &showProperties) {
    showWorkPeriodDialog(workPeriod);
  }
}

void CommunityView::mouseDoubleClickEvent(QMouseEvent * event)
{
  QModelIndex index = this->indexAt(event->pos());
  if (index.isValid()) {
    QVariant v = model()->data(index, CommunityModel::WorkPeriodRole);
    WorkPeriod * workPeriod = v.value<WorkPeriod*>();
    showWorkPeriodDialog(workPeriod);
  }
}

void CommunityView::removeWorkPeriod(WorkPeriod * workPeriod)
{
  QString title("Remove Work Period");
  QString text("Are you sure you want to remove the selected work period?");
  QMessageBox::StandardButton response = QMessageBox::question(this, title, text);
  if (response == QMessageBox::Yes) {
    QVariant v = model()->data(QModelIndex(), CommunityModel::CommunityRole);
    Community * community = v.value<Community*>();
    community->removeWorkPeriod(workPeriod);
    update();
  }
}

int CommunityView::showWorkPeriodDialog(WorkPeriod * workPeriod)
{
  WorkPeriodDialog dialog(this);
  dialog.setEnableCommunity(false);
  dialog.setStart(workPeriod->start());
  dialog.setEnd(workPeriod->end());
  dialog.setNotes(workPeriod->notes());

  int response = dialog.exec();
  if (response == QDialog::Accepted) {
    workPeriod->setStart(dialog.startTime());
    workPeriod->setEnd(dialog.endTime());
    workPeriod->setNotes(dialog.notes());
  }
  return response;
}
