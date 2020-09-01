#include "community.h"

#include <chrono>
#include <ctime>

Community::Community()
  : mWorking(false)
{
  mTimer.setInterval(1000);
  mTimer.stop();
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateWorkTime()));
}

void Community::updateWorkTime()
{
  emit workTimeIncrement();
}

void Community::startWork()
{
  if (mWorking)
    return;

  mCurrentWork.start = std::chrono::system_clock::now();
  mTimer.start();
  mWorking = true;
}

void Community::stopWork()
{
  if (!mWorking)
    return;

  mTimer.stop();
  mCurrentWork.stop = std::chrono::system_clock::now();
  mTimeWorked.push_back(mCurrentWork);
  mWorking = false;
}

int Community::totalTimeWorked() const
{
  int timeWorked = 0;
  for (std::size_t i = 0; i < mTimeWorked.size(); i++) {
    const WorkTime & workTime = mTimeWorked.at(i);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(workTime.stop - workTime.start);
    timeWorked += seconds.count();
  }

  if (mWorking) {
    auto t = std::chrono::system_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(t - mCurrentWork.start);
    timeWorked += seconds.count();
  }

  return timeWorked;
}
