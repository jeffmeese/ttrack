#include "workperiod.h"

#include "streamio.h"

#include <QDataStream>

static const QString TYPE_ID("WorkPeriod");
static const int32_t SAVE_VERSION = 1;

WorkPeriod::WorkPeriod()
{
  setStart(QDateTime::currentDateTime());
  setEnd(QDateTime::currentDateTime());
}

WorkPeriod::WorkPeriod(const QDateTime & start, const QDateTime & end)
{
  setStart(start);
  setEnd(end);
}

int WorkPeriod::duration() const
{
  QDateTime start(mStartDate, mStartTime);
  QDateTime end(mEndDate, mEndTime);

  return start.secsTo(end);
}

QDateTime WorkPeriod::end() const
{
  return QDateTime(mEndDate, mEndTime);
}

QDate WorkPeriod::endDate() const
{
  return mEndDate;
}

QTime WorkPeriod::endTime() const
{
  return mEndTime;
}

void WorkPeriod::loadFromDataStream(QDataStream &dataStream)
{
  int32_t version = 0;
  dataStream >> version;

  QDateTime startDateTime = QDateTime::fromString(streamio::readString(dataStream));
  QDateTime endDateTime = QDateTime::fromString(streamio::readString(dataStream));

  mStartDate = startDateTime.date();
  mStartTime = startDateTime.time();
  mEndDate = endDateTime.date();
  mEndTime = endDateTime.time();
}

void WorkPeriod::saveToDataStream(QDataStream &dataStream) const
{
  streamio::writeString(TYPE_ID, dataStream);
  dataStream << SAVE_VERSION;

  QDateTime start(mStartDate, mStartTime);
  streamio::writeString(start.toString(), dataStream);

  QDateTime end(mEndDate, mEndTime);
  streamio::writeString(end.toString(), dataStream);
}

QDateTime WorkPeriod::start() const
{
  return QDateTime(mStartDate, mStartTime);
}

QDate WorkPeriod::startDate() const
{
  return mStartDate;
}

QTime WorkPeriod::startTime() const
{
  return mStartTime;
}

void WorkPeriod::setEnd(const QDateTime & dateTime)
{
  mEndDate = dateTime.date();
  mEndTime = dateTime.time();
}

void WorkPeriod::setEndDate(const QDate & date)
{
  mEndDate = date;
}

void WorkPeriod::setEndTime(const QTime & time)
{
  mEndTime = time;
}

void WorkPeriod::setStart(const QDateTime & dateTime)
{
  mStartDate = dateTime.date();
  mStartTime = dateTime.time();
}

void WorkPeriod::setStartDate(const QDate & date)
{
  mStartDate = date;
}

void WorkPeriod::setStartTime(const QTime & time)
{
  mStartTime = time;
}
