#include "switch.h"

Switch::Switch(QWidget *parent)
  : QAbstractButton(parent)
  , mSwitch(false)
  , mHeight(10)
  , mMargin(10)
  , mOpacity(0.000)
  , mThumb("#d5d5d5")
  , mAnim(new QPropertyAnimation(this, "offset", this))
{
  setOffset(mHeight / 2);
  mY = mHeight / 2;
  setBrush(QColor("#009688"));
}

Switch::Switch(const QBrush &brush, QWidget *parent)
  : QAbstractButton(parent)
  , mSwitch(false)
  , mHeight(10)
  , mMargin(10)
  , mOpacity(0.000)
  , mThumb("#d5d5d5")
  , mAnim(new QPropertyAnimation(this, "offset", this))
{
  setOffset(mHeight / 2);
  mY = mHeight / 2;
  setBrush(brush);
}

//void Switch::paint(QPainter *painter, const QRect &, const QPalette &) const
//{
//  painter->save();
//  painter->setRenderHint(QPainter::Antialiasing, true);
//  painter->setPen(Qt::NoPen);
//  if (isEnabled()) {
//    painter->setBrush(mSwitch ? brush() : Qt::black);
//    painter->setOpacity(mSwitch ? 0.5 : 0.38);
//    painter->setRenderHint(QPainter::Antialiasing, true);
//    painter->drawRoundedRect(QRect(mMargin, mMargin, width() - 2*mMargin, height() - 2 * mMargin), 8.0, 8.0);
//    painter->setBrush(mThumb);
//    painter->setOpacity(1.0);
//    painter->drawEllipse(QRectF(offset() - (mHeight / 2), mY - (mHeight / 2)+8, height()-16, height()-16));
//  }
//  else {
//    painter->setBrush(Qt::black);
//    painter->setOpacity(0.12);
//    painter->drawRoundedRect(QRect(mMargin, mMargin, width() - 2*mMargin, height() - 2 * mMargin), 8.0, 8.0);
//    painter->setOpacity(1.0);
//    painter->setBrush(QColor("#BDBDBD"));
//    painter->drawEllipse(QRectF(offset() - (mHeight / 2), mY - (mHeight / 2), height(), height()));
//  }

//  painter->restore();
//}

void Switch::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.setPen(Qt::NoPen);
  if (isEnabled()) {
    p.setBrush(mSwitch ? brush() : Qt::black);
    p.setOpacity(mSwitch ? 0.5 : 0.38);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawRoundedRect(QRect(mMargin, mMargin, width() - 2*mMargin, height() - 2 * mMargin), 8.0, 8.0);
    p.setBrush(mThumb);
    p.setOpacity(1.0);
    p.drawEllipse(QRectF(offset() - (mHeight / 2), mY - (mHeight / 2)+8, height()-16, height()-16));
  }
  else {
    p.setBrush(Qt::black);
    p.setOpacity(0.12);
    p.drawRoundedRect(QRect(mMargin, mMargin, width() - 2*mMargin, height() - 2 * mMargin), 8.0, 8.0);
    p.setOpacity(1.0);
    p.setBrush(QColor("#BDBDBD"));
    p.drawEllipse(QRectF(offset() - (mHeight / 2), mY - (mHeight / 2), height(), height()));
  }
}

void Switch::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() & Qt::LeftButton) {
    setOn(!mSwitch);
  }
  QAbstractButton::mouseReleaseEvent(e);
}

void Switch::enterEvent(QEvent *e)
{
  setCursor(Qt::PointingHandCursor);
  QAbstractButton::enterEvent(e);
}

void Switch::setOn(bool value)
{
  mSwitch = value;
  mThumb = mSwitch ? mBrush : QBrush("#d5d5d5");
  if (mSwitch) {
    mAnim->setStartValue(mHeight / 2);
    mAnim->setEndValue(width() - mHeight);
    mAnim->setDuration(120);
    mAnim->start();
  }
  else {
    mAnim->setStartValue(offset());
    mAnim->setEndValue(mHeight / 2);
    mAnim->setDuration(120);
    mAnim->start();
  }
  update();
}

QSize Switch::sizeHint() const
{
  return QSize(2 * (mHeight + mMargin)-mMargin, mHeight + 2 * mMargin);
}
