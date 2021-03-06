#ifndef COMMUNITYMODEL_H
#define COMMUNITYMODEL_H

#include <QAbstractTableModel>

class Community;

class CommunityModel
    : public QAbstractTableModel
{
public:
  static const int CommunityRole = Qt::UserRole;
  static const int WorkPeriodRole = Qt::UserRole + 1;

public:
  CommunityModel();
  ~CommunityModel();

public:
  Community * community();
  const Community * community() const;
  void setCommunity(Community * community);

public:
  int columnCount(const QModelIndex & parent = QModelIndex()) const override;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientataion, int role = Qt::DisplayRole) const override;
  QModelIndex parent(const QModelIndex & index) const override;
  int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
  QString formatTime(int seconds) const;

private:
  Community * mCommunity;
};

#endif // COMMUNITYMODEL_H
