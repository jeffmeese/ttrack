#include "communitydelegate.h"

#include <QDebug>
#include <QPainter>

CommunityDelegate::CommunityDelegate()
{
}

void CommunityDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  const QRect r = option.rect;
  int h = 1;
  int margin = 10;
  int offset = r.height() / 2;

  QRect sliderRect(r.left() + margin, r.top() + margin, 30, r.height() - 2*margin);
  QRectF thumbRect(r.left() + offset, r.top() + 8, r.height()-16, r.height()-16);

  bool isOn = index.data().toBool();
  if (isOn) {
    QBrush sliderBrush(QColor("#009688"));
    painter->setBrush(sliderBrush);
    painter->setOpacity(0.5);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRoundedRect(sliderRect, 8.0, 8.0);

    QRectF thumbRect(r.left() + offset - (h / 2)+10, r.top() + 8, r.height()-16, r.height()-16);
    QBrush thumbBrush(QColor("#d5d5d5"));
    painter->setOpacity(1.0);
    painter->setBrush(thumbBrush);
    painter->drawEllipse(thumbRect);
  }
  else {
    QBrush sliderBrush(Qt::black);
    painter->setBrush(sliderBrush);
    painter->setOpacity(0.38);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRoundedRect(sliderRect, 8.0, 8.0);

    QBrush thumbBrush(QColor("#d5d5d5"));
    painter->setBrush(thumbBrush);
    painter->setOpacity(1.0);
    painter->drawEllipse(thumbRect);
  }
}
