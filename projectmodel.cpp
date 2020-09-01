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
        int timeWorked  = community->totalTimeWorked();
        return QString::number(timeWorked) + " seconds";
      }
    }
  }
  return QVariant();
}

void ProjectModel::handleCommunityUpdate()
{
  qDebug() << QObject::tr(__FUNCTION__);

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

QModelIndex ProjectModel::parent(const QModelIndex & index) const
{
  return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex & parent) const
{
  return (mProject != nullptr) ? mProject->totalCommunities() : 0;
}

void ProjectModel::setProject(Project *project)
{
  mProject = project;
  if (mProject != nullptr) {
    for (std::size_t i = 0; i < mProject->totalCommunities(); i++) {
      Community * c = mProject->getCommunity(i);
      connect(c, SIGNAL(workTimeIncrement()), SLOT(handleCommunityUpdate()));
    }
  }
}
