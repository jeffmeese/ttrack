#include "community.h"

#include "workperiod.h"

#include <chrono>
#include <ctime>

Community::Community()
  : mWorking(false)
{
  mTimer.setInterval(1000);
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateWorkPeriod()));
}

void Community::addWorkPeriod(std::unique_ptr<WorkPeriod> workPeriod)
{
  mWorkPeriods.push_back(std::move(workPeriod));
}

WorkPeriod * Community::getWorkPeriod(std::size_t index)
{
  return mWorkPeriods.at(index).get();
}

const WorkPeriod * Community::getWorkPeriod(std::size_t index) const
{
  return mWorkPeriods.at(index).get();
}

void Community::startWork()
{
  if (mWorking)
    return;

  mCurrentWorkPeriod.reset(new WorkPeriod);
  mCurrentWorkPeriod->setStartTime(std::chrono::system_clock::now());
  mTimer.start();
  mWorking = true;
}

void Community::stopWork()
{
  if (!mWorking)
    return;

  mTimer.stop();
  mCurrentWorkPeriod->setStopTime(std::chrono::system_clock::now());
  mWorkPeriods.push_back(std::move(mCurrentWorkPeriod));
  mWorking = false;
}

int Community::totalTimeWorked() const
{
  int timeWorked = 0;
  for (std::size_t i = 0; i < mWorkPeriods.size(); i++) {
    const WorkPeriod * workPeriod = mWorkPeriods.at(i).get();
    timeWorked += workPeriod->duration();
  }

  if (mWorking) {
    mCurrentWorkPeriod->setStopTime(std::chrono::system_clock::now());
    timeWorked += mCurrentWorkPeriod->duration();
  }

  return timeWorked;
}

std::size_t Community::totalWorkPeriods() const
{
  return mWorkPeriods.size();
}

void Community::updateWorkPeriod()
{
  mCurrentWorkPeriod->setStopTime(std::chrono::system_clock::now());
  emit changed();
}
