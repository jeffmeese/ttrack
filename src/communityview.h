#ifndef COMMUNITYVIEW_H
#define COMMUNITYVIEW_H

#include <QTableView>

class CommunityView : public QTableView
{
  Q_OBJECT

public:
  explicit CommunityView(QWidget * parentWidget = nullptr);

protected:
  void mousePressEvent(QMouseEvent * event) override;

private slots:
  void handleIndexClick(const QModelIndex & index);
};

#endif // COMMUNITYVIEW_H
