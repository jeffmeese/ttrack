#ifndef OVERVIEWTABDELEGATE_H
#define OVERVIEWTABDELEGATE_H

#include <QStyledItemDelegate>

class OverviewTabDelegate
    : public QStyledItemDelegate
{
  Q_OBJECT

public:
  OverviewTabDelegate();

protected:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // OVERVIEWTABDELEGATE_H
