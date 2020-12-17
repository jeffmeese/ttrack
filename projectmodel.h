#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractTableModel>

class Community;
class Project;

class ProjectModel
    : public QAbstractTableModel
{
  Q_OBJECT

public:
  ProjectModel();

public:
  Project * project();
  const Project * project() const;
  void setProject(Project * project);

public:
  int columnCount(const QModelIndex & parent = QModelIndex()) const override;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientataion, int role = Qt::DisplayRole) const override;
  QModelIndex parent(const QModelIndex & index) const override;
  int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
  QString formatTime(int seconds) const;

private slots:
  void handleAddCommunity(Community * community);
  void handleProjectModified();

private:
  Project * mProject;
};

inline Project * ProjectModel::project()
{
  return mProject;
}

inline const Project * ProjectModel::project() const
{
  return mProject;
}

#endif // PROJECTMODEL_H
