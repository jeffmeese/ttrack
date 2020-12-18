#ifndef COMMUNITYDELEGATE_H
#define COMMUNITYDELEGATE_H

#include <QStyledItemDelegate>

class CommunityDelegate
    : public QStyledItemDelegate
{
  Q_OBJECT

public:
  CommunityDelegate();

protected:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COMMUNITYDELEGATE_H
