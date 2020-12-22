#ifndef WORKPERIOD_H
#define WORKPERIOD_H

#include <chrono>

#include <QDate>
#include <QTime>

class WorkPeriod
{
public:
  using TimePoint = std::chrono::system_clock::time_point;

public:
  WorkPeriod();
  WorkPeriod(const QDateTime & start, const QDateTime & end);

public:
  QDateTime end() const;
  QDate endDate() const;
  QTime endTime() const;
  QString notes() const;
  QDateTime start() const;
  QDate startDate() const;
  QTime startTime() const;
  void setEnd(const QDateTime & dateTime);
  void setEndDate(const QDate & date);
  void setEndTime(const QTime & time);
  void setNotes(const QString & notes);
  void setStart(const QDateTime & dateTime);
  void setStartDate(const QDate & date);
  void setStartTime(const QTime & time);

public:
  int duration() const;
  void loadFromDataStream(QDataStream & dataStream);
  void saveToDataStream(QDataStream & dataStream) const;

private:
  QDate mEndDate;
  QTime mEndTime;
  QDate mStartDate;
  QTime mStartTime;
  QString mNotes;
};


#endif // WORKPERIOD_H
