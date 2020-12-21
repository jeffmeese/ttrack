#include "overviewtabview.h"
#include "overviewtabdelegate.h"

#include "community.h"
#include "communitydialog.h"

#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QMouseEvent>

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
  QAction removeCommunity("Remove");
  QAction showWork("Show Work Periods");
  QAction showProperties("Properties");

  Community * community = nullptr;
  QModelIndex index = indexAt(pt);
  if (index.isValid()) {
    QVariant v = model()->data(index, Qt::UserRole);
    community = v.value<Community*>();
    popupMenu.addAction(&showWork);
    popupMenu.addAction(&removeCommunity);
    popupMenu.addAction(&showProperties);
  }
  else {
    popupMenu.addAction(&addCommunity);
  }

  QAction * selectedAction = popupMenu.exec(viewport()->mapToGlobal(pt));
  if (selectedAction == &addCommunity) {

  }
  else if (selectedAction == &removeCommunity) {

  }
  else if (selectedAction == &showWork) {
    emit showCommunity(community);
  }
  else if (selectedAction == &showProperties) {
    showPropertiesDialog(community);
  }

}

void OverviewTabView::handleIndexClick(const QModelIndex & index)
{
  if (index.column() != 0)
    return;

  bool value = model()->data(index).toBool();
  model()->setData(index, !value);
}

void OverviewTabView::showPropertiesDialog(Community * community)
{
  CommunityDialog dialog(this);
  dialog.setName(community->name());
  dialog.setDescription(community->description());
  for (std::size_t i = 0; i < community->totalBoardMembers(); i++) {
    BoardMember * boardMember = community->getBoardMember(i);
    dialog.addBoardMember(*boardMember);
  }

  int response = dialog.exec();
  if (response == QDialog::Rejected)
    return;

  QString name = dialog.name();
  community->setName(name);
  community->removeAllBoardMembers();
  for (std::size_t i = 0; i < dialog.totalBoardMembers(); i++) {
    BoardMember boardMember = dialog.getBoardMember(i);
    std::unique_ptr<BoardMember> newBoardMember(new BoardMember(boardMember));
    community->addBoardMember(std::move(newBoardMember));
  }
}
