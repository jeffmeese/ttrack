#include "community.h"

#include "workperiod.h"

#include <chrono>
#include <ctime>

#include <QDate>

Community::Community()
  : mActive(true)
  , mWorking(false)
{
  mTimer.setInterval(1000);
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateWorkPeriod()));
}

Community::~Community()
{

}

bool Community::active() const
{
  return mActive;
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

void Community::setActive(bool value)
{
  mActive = value;
}

void Community::startWork()
{
  if (mWorking)
    return;

  mCurrentWorkPeriod.reset(new WorkPeriod);
  mCurrentWorkPeriod->setStart(QDateTime::currentDateTime());
  mTimer.start();
  mWorking = true;
}

void Community::stopWork()
{
  if (!mWorking)
    return;

  mTimer.stop();
  mCurrentWorkPeriod->setEnd(QDateTime::currentDateTime());
  mWorkPeriods.push_back(std::move(mCurrentWorkPeriod));
  mWorking = false;
}

int Community::timeWorkedToday() const
{
  QDate date = QDate::currentDate();
  int timeWorked = 0;
  for (std::size_t i = 0; i < mWorkPeriods.size(); i++) {
    const WorkPeriod * workPeriod = mWorkPeriods.at(i).get();
    QDateTime start = workPeriod->start();
    QDateTime end = workPeriod->end();
    if (start.date().year() == date.year() && start.date().month() == date.month() && start.date().day() == date.day()) {
      timeWorked += workPeriod->duration();
    }
    timeWorked += workPeriod->duration();
  }
  return timeWorked;
}

int Community::totalTimeWorked() const
{
  int timeWorked = 0;
  for (std::size_t i = 0; i < mWorkPeriods.size(); i++) {
    const WorkPeriod * workPeriod = mWorkPeriods.at(i).get();
    timeWorked += workPeriod->duration();
  }

  if (mWorking) {
    mCurrentWorkPeriod->setEnd(QDateTime::currentDateTime());
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
  mCurrentWorkPeriod->setEnd(QDateTime::currentDateTime());
  //mCurrentWorkPeriod->setStopTime(std::chrono::system_clock::now());
  emit changed();
}
