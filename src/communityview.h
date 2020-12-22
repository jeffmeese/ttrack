#ifndef COMMUNITYVIEW_H
#define COMMUNITYVIEW_H

#include <QTableView>

class WorkPeriod;

class CommunityView
    : public QTableView
{
  Q_OBJECT

public:
  explicit CommunityView(QWidget * parentWidget = nullptr);

protected:
  void mouseDoubleClickEvent(QMouseEvent * event) override;

private slots:
  void handleContextMenu(const QPoint & pos);

private:
  void addWorkPeriod();
  void removeWorkPeriod(WorkPeriod * workPeriod);
  int showWorkPeriodDialog(WorkPeriod * workPeriod);
};

#endif // COMMUNITYVIEW_H
