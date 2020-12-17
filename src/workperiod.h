#ifndef WORKPERIOD_H
#define WORKPERIOD_H

#include <chrono>

class WorkPeriod
{
public:
  using TimePoint = std::chrono::system_clock::time_point;

public:
  WorkPeriod();
  WorkPeriod(const TimePoint & start);
  WorkPeriod(const TimePoint & start, const TimePoint & stop);

public:
  TimePoint startTime() const;
  TimePoint stopTime() const;
  void setStartTime(const TimePoint & value);
  void setStopTime(const TimePoint & value);

public:
  int duration() const;

private:
  TimePoint mStart;
  TimePoint mStop;
};

inline WorkPeriod::TimePoint WorkPeriod::startTime() const
{
  return mStart;
}

inline WorkPeriod::TimePoint WorkPeriod::stopTime() const
{
  return mStop;
}

inline void WorkPeriod::setStartTime(const TimePoint & value)
{
  mStart = value;
}

inline void WorkPeriod::setStopTime(const TimePoint & value)
{
  mStop = value;
}


#endif // WORKPERIOD_H
