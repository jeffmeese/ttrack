#ifndef OVERVIEWTABVIEW_H
#define OVERVIEWTABVIEW_H

#include <QTableView>

class Community;

class OverviewTabView
    : public QTableView
{
  Q_OBJECT

public:
  explicit OverviewTabView(QWidget * parentWidget = nullptr);

protected:
  void mouseDoubleClickEvent(QMouseEvent * event) override;

private slots:
  void handleContextMenu(const QPoint & point);
  void handleIndexClick(const QModelIndex & index);

private:
  void handleAddCommunity();
  void handleAddWorkPeriod(Community * community);
  void handleRemoveCommunity(Community * community);
  void showPropertiesDialog(Community * community);

signals:
  void showCommunity(Community * community);
};

#endif // OVERVIEWTABVIEW_H
