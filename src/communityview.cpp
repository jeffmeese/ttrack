#include "communityview.h"

#include "communitydelegate.h"

#include <QDebug>
#include <QMouseEvent>

CommunityView::CommunityView(QWidget * parentWidget)
  : QTableView(parentWidget)
{
  setItemDelegateForColumn(0, new CommunityDelegate);
  connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(handleIndexClick(QModelIndex)));
}

void CommunityView::handleIndexClick(const QModelIndex & index)
{
  if (index.column() != 0)
    return;

  bool value = model()->data(index).toBool();
  model()->setData(index, !value);
}

void CommunityView::mousePressEvent(QMouseEvent * event)
{
  qDebug() << QObject::tr(__FUNCTION__);
  QTableView::mousePressEvent(event);
}
