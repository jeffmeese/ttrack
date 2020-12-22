#include "overviewtabmodel.h"

#include "community.h"
#include "project.h"

#include <QDebug>

OverviewTabModel::OverviewTabModel()
  : mProject(nullptr)
{
}

int OverviewTabModel::columnCount(const QModelIndex &) const
{
  return 6;
}

QVariant OverviewTabModel::data(const QModelIndex & index, int role) const
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
        return community->active();
      }
      else if (col == 2) {
        return community->name();
      }
      else if (col == 3) {
        return formatTime(community->timeWorkedToday());
      }
      else if (col == 4) {
        return formatTime(community->timeWorkedThisWeek());
      }
      else if (col == 5) {
        return formatTime(community->timeWorkedThisMonth());
      }
    }
  }

  if (role == CommunityRole) {
    int row = index.row();
    Community * community = mProject->getCommunity(row);

    QVariant v;
    v.setValue(community);
    return v;
  }

  if (role == ProjectRole) {
    QVariant v;
    v.setValue(mProject);
    return v;
  }

  return QVariant();
}

QString OverviewTabModel::formatTime(int seconds) const
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

void OverviewTabModel::handleAddCommunity(Community * community)
{
  connect(community, SIGNAL(changed()), SLOT(handleCommunityChanged()));
  emit layoutChanged();
}

void OverviewTabModel::handleCommunityChanged()
{
  emit layoutChanged();
}

void OverviewTabModel::handleProjectModified()
{
  emit layoutChanged();
}

QVariant OverviewTabModel::headerData(int section, Qt::Orientation orientataion, int role) const
{
  if (role == Qt::DisplayRole) {
    if (orientataion == Qt::Horizontal) {
      if (section == 0) {
        return "Status";
      }
      else if (section == 1) {
        return "Active";
      }
      else if (section == 2) {
        return "Community";
      }
      else if (section == 3) {
        return "Time Today";
      }
      else if (section == 4) {
        return "Time This Week";
      }
      else if (section == 5) {
        return "Time This Month";
      }
    }
  }
  return QVariant();
}

QModelIndex OverviewTabModel::parent(const QModelIndex &) const
{
  return QModelIndex();
}

int OverviewTabModel::rowCount(const QModelIndex &) const
{
  return (mProject != nullptr) ? static_cast<int>(mProject->totalCommunities()) : 0;
}

bool OverviewTabModel::setData(const QModelIndex & index, const QVariant & value, int role)
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
  return true;
}

void OverviewTabModel::setProject(Project *project)
{
  mProject = project;
  if (mProject != nullptr) {
    emit layoutAboutToBeChanged();
    connect(mProject, SIGNAL(communityAdded(Community *)), SLOT(handleAddCommunity(Community*)));
    connect(mProject, SIGNAL(modified(bool)), SLOT(handleProjectModified()));
    emit layoutChanged();
  }
}
