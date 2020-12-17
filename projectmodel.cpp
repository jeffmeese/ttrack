#include "projectmodel.h"

#include "community.h"
#include "project.h"

#include <QDebug>

ProjectModel::ProjectModel()
  : mProject(nullptr)
{
}

int ProjectModel::columnCount(const QModelIndex &) const
{
  return 3;
}

QVariant ProjectModel::data(const QModelIndex & index, int role) const
{
  if (mProject == nullptr)
    return QVariant();

  if (role == Qt::DisplayRole) {
    int row = index.row();
    int col = index.column();
    if (row < (int)mProject->totalCommunities()) {
      const Community * community = mProject->getCommunity(row);
      if (col == 1) {
        return community->name();
      }
      else if (col == 2) {
        return formatTime(community->totalTimeWorked());
      }
    }
  }
  return QVariant();
}

QString ProjectModel::formatTime(int seconds) const
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

void ProjectModel::handleAddCommunity(Community *)
{
  emit layoutChanged();
}

void ProjectModel::handleProjectModified()
{
  emit layoutChanged();
}

QVariant ProjectModel::headerData(int section, Qt::Orientation orientataion, int role) const
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
        return "Total Time";
      }
    }
  }
  return QVariant();
}

QModelIndex ProjectModel::parent(const QModelIndex &) const
{
  return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex &) const
{
  return (mProject != nullptr) ? static_cast<int>(mProject->totalCommunities()) : 0;
}

void ProjectModel::setProject(Project *project)
{
  mProject = project;
  if (mProject != nullptr) {
    connect(mProject, SIGNAL(communityAdded(Community *)), SLOT(handleAddCommunity(Community*)));
    connect(mProject, SIGNAL(modified(bool)), SLOT(handleProjectModified()));
  }
}
