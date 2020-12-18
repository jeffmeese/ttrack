#include "communitymodel.h"

#include "community.h"
#include "project.h"

#include <QDebug>

CommunityModel::CommunityModel()
  : mProject(nullptr)
{
}

int CommunityModel::columnCount(const QModelIndex &) const
{
  return 5;
}

QVariant CommunityModel::data(const QModelIndex & index, int role) const
{
  if (mProject == nullptr)
    return QVariant();

  if (role == Qt::DisplayRole) {
    int row = index.row();
    int col = index.column();
    if (row < (int)mProject->totalCommunities()) {
      const Community * community = mProject->getCommunity(row);
      if (col == 0) {
        return community->working();
      }
      else if (col == 1) {
        return community->name();
      }
      else if (col == 2) {
        return formatTime(community->totalTimeWorked());
      }
      else if (col == 3) {
        return formatTime(community->totalTimeWorked());
      }
      else if (col == 4) {
        return formatTime(community->totalTimeWorked());
      }
    }
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

void CommunityModel::handleAddCommunity(Community * community)
{
  int totalRows = rowCount();

  emit layoutChanged();
}

void CommunityModel::handleProjectModified()
{
  emit layoutChanged();
}

QVariant CommunityModel::headerData(int section, Qt::Orientation orientataion, int role) const
{
  if (role == Qt::DisplayRole) {
    if (orientataion == Qt::Horizontal) {
      if (section == 0) {
        return "Status";
      }
      else if (section == 1) {
        return "Community";
      }
      else if (section == 2) {
        return "Time Today";
      }
      else if (section == 3) {
        return "Time This Week";
      }
      else if (section == 4) {
        return "Time This Month";
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
  return (mProject != nullptr) ? static_cast<int>(mProject->totalCommunities()) : 0;
}

bool CommunityModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
  if (role != Qt::EditRole)
    return QAbstractTableModel::setData(index, value, role);

  if (index.column() != 0) {
    return QAbstractTableModel::setData(index, value, role);
  }

  bool v = value.toBool();
  Community * community = mProject->getCommunity(index.row());
  if (v)
    community->startWork();
  else
    community->stopWork();

  emit layoutChanged();
}

void CommunityModel::setProject(Project *project)
{
  mProject = project;
  if (mProject != nullptr) {
    connect(mProject, SIGNAL(communityAdded(Community *)), SLOT(handleAddCommunity(Community*)));
    connect(mProject, SIGNAL(modified(bool)), SLOT(handleProjectModified()));
  }
}