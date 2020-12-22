#ifndef OVERVIEWTABMODEL_H
#define OVERVIEWTABMODEL_H

#include <QAbstractTableModel>

class Community;
class Project;

class OverviewTabModel
    : public QAbstractTableModel
{
  Q_OBJECT

public:
  static const int CommunityRole = Qt::UserRole;
  static const int ProjectRole = Qt::UserRole+1;

public:
  OverviewTabModel();

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
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

private:
  QString formatTime(int seconds) const;

private slots:
  void handleAddCommunity(Community * community);
  void handleCommunityChanged();
  void handleProjectModified();

private:
  Project * mProject;
};

#endif // OVERVIEWTABMODEL_H
