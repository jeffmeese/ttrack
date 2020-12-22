#include "overviewtabview.h"

#include "overviewtabdelegate.h"
#include "overviewtabmodel.h"

#include "community.h"
#include "communitydialog.h"
#include "project.h"
#include "workperioddialog.h"

#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>

Q_DECLARE_METATYPE(Project*);

OverviewTabView::OverviewTabView(QWidget * parentWidget)
  : QTableView(parentWidget)
{
  this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  setItemDelegateForColumn(0, new OverviewTabDelegate);
  connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(handleIndexClick(QModelIndex)));
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(handleContextMenu(QPoint)));
}

void OverviewTabView::handleContextMenu(const QPoint & pt)
{
  QMenu popupMenu(this);
  QAction addCommunity("Add Community");
  QAction removeCommunity("Remove Community");
  QAction showWork("Show Work Periods");
  QAction showProperties("Properties");
  QAction addWorkPeriod("Add Work Period");

  Community * community = nullptr;
  QModelIndex index = indexAt(pt);
  if (index.isValid()) {
    QVariant v = model()->data(index, OverviewTabModel::CommunityRole);
    community = v.value<Community*>();
    popupMenu.addAction(&addWorkPeriod);
    popupMenu.addAction(&showWork);
    popupMenu.addSeparator();
    popupMenu.addAction(&removeCommunity);
    popupMenu.addAction(&showProperties);
  }
  else {
    popupMenu.addAction(&addCommunity);
    popupMenu.addAction(&addWorkPeriod);
  }

  QAction * selectedAction = popupMenu.exec(viewport()->mapToGlobal(pt));
  if (selectedAction == &addCommunity) {
    handleAddCommunity();
  }
  else if (selectedAction == &removeCommunity) {
    handleRemoveCommunity(community);
  }
  else if (selectedAction == &showWork) {
    emit showCommunity(community);
  }
  else if (selectedAction == &showProperties) {
    showPropertiesDialog(community);
  }
  else if (selectedAction == &addWorkPeriod) {
    handleAddWorkPeriod(community);
  }

}

void OverviewTabView::handleAddCommunity()
{
  CommunityDialog dialog(this);
  dialog.setActive(true);
  int response = dialog.exec();
  if (response == QDialog::Rejected) {
    return;
  }

  QString name = dialog.name();
  std::unique_ptr<Community> community(new Community);
  community->setName(name);
  community->setDescription(dialog.description());
  for (int i = 0; i < dialog.totalBoardMembers(); i++) {
    BoardMember boardMember = dialog.getBoardMember(i);
    std::unique_ptr<BoardMember> newBoardMember(new BoardMember(boardMember));
    community->addBoardMember(std::move(newBoardMember));
  }
  //mProject->addCommunity(std::move(community));
}

void OverviewTabView::handleIndexClick(const QModelIndex & index)
{
  if (index.column() != 0)
    return;

  bool value = model()->data(index).toBool();
  model()->setData(index, !value);
}

void OverviewTabView::handleRemoveCommunity(Community * community)
{
  QString title("Remove Community");
  QString text("Are you sure you want to remove the selected community?");
  QMessageBox::StandardButton response = QMessageBox::question(this, title, text);
  if (response == QMessageBox::Yes) {
    QVariant v = model()->data(QModelIndex(), OverviewTabModel::ProjectRole);
    Project * project = v.value<Project*>();
    project->removeCommunity(community);
    update();
  }
}

void OverviewTabView::mouseDoubleClickEvent(QMouseEvent * event)
{
  QModelIndex index = this->indexAt(event->pos());
  if (index.isValid()) {
    QVariant v = model()->data(index, Qt::UserRole);
    Community * community = v.value<Community*>();
    emit showCommunity(community);
  }
}

void OverviewTabView::showPropertiesDialog(Community * community)
{
  CommunityDialog dialog(this);
  dialog.setActive(community->active());
  dialog.setName(community->name());
  dialog.setDescription(community->description());
  for (std::size_t i = 0; i < community->totalBoardMembers(); i++) {
    BoardMember * boardMember = community->getBoardMember(i);
    dialog.addBoardMember(*boardMember);
  }

  int response = dialog.exec();
  if (response == QDialog::Rejected)
    return;

  community->setActive(dialog.active());
  community->setName(dialog.name());
  community->removeAllBoardMembers();
  for (int i = 0; i < dialog.totalBoardMembers(); i++) {
    BoardMember boardMember = dialog.getBoardMember(i);
    std::unique_ptr<BoardMember> newBoardMember(new BoardMember(boardMember));
    community->addBoardMember(std::move(newBoardMember));
  }
}
