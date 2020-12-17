#include "workperiod.h"

WorkPeriod::WorkPeriod()
{
  mStart = std::chrono::system_clock::now();
  mStop = std::chrono::system_clock::now();
}

WorkPeriod::WorkPeriod(const TimePoint & start)
{
  mStart = start;
  mStop = start;
}

WorkPeriod::WorkPeriod(const TimePoint & start, const TimePoint & stop)
{
  mStart = start;
  mStop = stop;
}

int WorkPeriod::duration() const
{
  return std::chrono::duration_cast<std::chrono::seconds>(mStop - mStart).count();
}
