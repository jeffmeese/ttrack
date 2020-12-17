#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QAbstractTableModel>

class Community;
class Project;

class ReportModel
    : public QAbstractTableModel
{
  Q_OBJECT

public:
  ReportModel();

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

#endif // REPORTMODEL_H
