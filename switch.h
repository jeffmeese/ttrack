#ifndef SWITCH_H
#define SWITCH_H

#include <QtWidgets>

class Switch
    : public QAbstractButton
{
  Q_OBJECT
  Q_PROPERTY(int offset READ offset WRITE setOffset)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
  Switch(QWidget* parent = nullptr);
  Switch(const QBrush& brush, QWidget* parent = nullptr);

  QSize sizeHint() const override;
  QBrush brush() const;
  int offset() const;
  void setBrush(const QBrush &brsh);
  void setOffset(int o);

protected:
  void paintEvent(QPaintEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void enterEvent(QEvent*) override;

private:
  bool mSwitch;
  qreal mOpacity;
  int mX;
  int mY;
  int mHeight;
  int mMargin;
  QBrush mThumb;
  QBrush mTrack;
  QBrush mBrush;
  QPropertyAnimation *mAnim = nullptr;
};

inline QBrush Switch::brush() const
{
  return mBrush;
}

inline void Switch::setBrush(const QBrush &brsh)
{
  mBrush = brsh;
}

inline int Switch::offset() const
{
  return mX;
}

inline void Switch::setOffset(int o)
{
  mX = o;
  update();
}

#endif
