#include "communitymodel.h"
#include "community.h"
#include "workperiod.h"

Q_DECLARE_METATYPE(Community*);

CommunityModel::CommunityModel()
  : mCommunity(nullptr)
{
}

CommunityModel::~CommunityModel()
{

}

int CommunityModel::columnCount(const QModelIndex &) const
{
  return 3;
}

QVariant CommunityModel::data(const QModelIndex & index, int role) const
{
  if (mCommunity == nullptr)
    return QVariant();

  if (role == Qt::DisplayRole) {
    int row = index.row();
    int col = index.column();
    if (row < static_cast<int>(mCommunity->totalWorkPeriods())) {
      WorkPeriod * workPeriod = mCommunity->getWorkPeriod(row);
      if (col == 0) {
        return workPeriod->start();
      }
      else if (col == 1) {
        return workPeriod->end();
      }
      else if (col == 2) {
        return workPeriod->duration();
      }
    }
  }

  return QVariant();
}

//QString OverviewTabModel::formatTime(int seconds) const
//{
//  int hours = 0, minutes = 0;
//  while (seconds >= 3600) {
//    hours++;
//    seconds -= 3600;
//  }
//  while (seconds >= 60) {
//    minutes++;
//    seconds -= 60;
//  }
//  QString s1 = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
//                                  .arg(minutes, 2, 10, QChar('0'))
//                                  .arg(seconds, 2, 10, QChar('0'));
//  return s1;
//}

//void OverviewTabModel::handleAddCommunity(Community * community)
//{
//  connect(community, SIGNAL(changed()), SLOT(handleCommunityChanged()));
//  emit layoutChanged();
//}

//void CommunityModel::handleCommunityChanged()
//{
//  emit layoutChanged();
//}

//void CommunityModel::handleProjectModified()
//{
//  emit layoutChanged();
//}

QVariant CommunityModel::headerData(int section, Qt::Orientation orientataion, int role) const
{
  if (role == Qt::DisplayRole) {
    if (orientataion == Qt::Horizontal) {
      if (section == 0) {
        return "Start Date";
      }
      else if (section == 1) {
        return "End Date";
      }
      else if (section == 2) {
        return "Total Time Worked";
      }
    }
  }
  return QVariant();
}

QModelIndex CommunityModel::parent(const QModelIndex &) const
{
  return QModelIndex();
}

int CommunityModel::rowCount(const QModelIndex &) const
{
  return (mCommunity != nullptr) ? static_cast<int>(mCommunity->totalWorkPeriods()) : 0;
}

//bool CommunityModel::setData(const QModelIndex & index, const QVariant & value, int role)
//{
//  if (role != Qt::EditRole)
//    return QAbstractTableModel::setData(index, value, role);

//  if (index.column() != 0) {
//    return QAbstractTableModel::setData(index, value, role);
//  }

//  bool v = value.toBool();
//  Community * community = mProject->getCommunity(index.row());
//  if (v)
//    community->startWork();
//  else
//    community->stopWork();

//  emit layoutChanged();
  //return true;
//}

void CommunityModel::setCommunity(Community *community)
{
  mCommunity = community;
  if (mCommunity != nullptr) {
    connect(community, SIGNAL(changed()), SIGNAL(layoutChanged()));
    //connect(community, SIGNAL(communityAdded(Community *)), SLOT(handleAddCommunity(Community*)));
    //connect(community, SIGNAL(modified(bool)), SLOT(handleProjectModified()));
  }
}
