#include "communitymodel.h"
#include "community.h"
#include "workperiod.h"

Q_DECLARE_METATYPE(Community*);
Q_DECLARE_METATYPE(WorkPeriod*);

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
    if (!index.isValid())
      return QVariant();

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
        return formatTime(workPeriod->duration());
      }
    }
  }

  if (role == CommunityRole) {
    QVariant v;
    v.setValue(mCommunity);
    return v;
  }

  if (role == WorkPeriodRole) {
    if (!index.isValid()) {
      return QVariant();
    }

    int row = index.row();
    WorkPeriod * workPeriod = mCommunity->getWorkPeriod(row);

    QVariant v;
    v.setValue(workPeriod);
    return v;
  }

  return QVariant();
}

QString CommunityModel::formatTime(int seconds) const
{
  int hours = 0, minutes = 0;
  while (seconds >= 3600) {
    hours++;
    seconds -= 3600;
  }
  while (seconds >= 60) {
    minutes++;
    seconds -= 60;
  }
  QString s1 = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                                  .arg(minutes, 2, 10, QChar('0'))
                                  .arg(seconds, 2, 10, QChar('0'));
  return s1;
}

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

void CommunityModel::setCommunity(Community *community)
{
  mCommunity = community;
  if (mCommunity != nullptr) {
    connect(community, SIGNAL(changed()), SIGNAL(layoutChanged()));
  }
}
