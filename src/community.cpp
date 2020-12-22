#include "community.h"

#include "boardmember.h"
#include "streamio.h"
#include "workperiod.h"

#include <chrono>
#include <cstdint>
#include <ctime>

#include <QDataStream>
#include <QDate>
#include <QDebug>

static const QString TYPE_ID("Community");
static const int32_t SAVE_VERSION = 1;

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

void Community::addBoardMember(std::unique_ptr<BoardMember> boardMember)
{
  mBoardMembers.push_back(std::move(boardMember));
  emit changed();
}

void Community::addWorkPeriod(std::unique_ptr<WorkPeriod> workPeriod)
{
  mWorkPeriods.push_back(std::move(workPeriod));
  emit changed();
}

QString Community::description() const
{
  return mDescription;
}

BoardMember * Community::getBoardMember(std::size_t index)
{
  return mBoardMembers.at(index).get();
}

const BoardMember * Community::getBoardMember(std::size_t index) const
{
  return mBoardMembers.at(index).get();
}

WorkPeriod * Community::getWorkPeriod(std::size_t index)
{
  return mWorkPeriods.at(index).get();
}

const WorkPeriod * Community::getWorkPeriod(std::size_t index) const
{
  return mWorkPeriods.at(index).get();
}

void Community::loadFromDataStream(QDataStream &dataStream)
{
  int32_t version = streamio::readInt32(dataStream);
  mName = streamio::readString(dataStream);
  mDescription = streamio::readString(dataStream);
  mActive = (streamio::readInt32(dataStream) > 0);

  mBoardMembers.clear();
  int32_t numBoardMembers = streamio::readInt32(dataStream);
  for (int32_t i = 0;i < numBoardMembers; i++) {
    streamio::readString(dataStream); // Skip the ID portion
    std::unique_ptr<BoardMember> boardMember(new BoardMember);
    boardMember->loadFromDataStream(dataStream);
    mBoardMembers.push_back(std::move(boardMember));
  }

  mWorkPeriods.clear();
  int32_t numWorkPeriods = streamio::readInt32(dataStream);
  for (int32_t i = 0; i < numWorkPeriods; i++) {
    streamio::readString(dataStream); // Skip the ID portion
    WorkPeriodPtr workPeriod(new WorkPeriod);
    workPeriod->loadFromDataStream(dataStream);
    mWorkPeriods.push_back(std::move(workPeriod));
  }
}

QString Community::name() const
{
  return mName;
}

void Community::removeAllBoardMembers()
{
  mBoardMembers.clear();
  emit changed();
}

bool Community::removeWorkPeriod(WorkPeriod *workPeriod)
{
  for (WorkPeriodVector::iterator itr = mWorkPeriods.begin(); itr != mWorkPeriods.end(); ++itr) {
    if (itr->get() == workPeriod) {
      mWorkPeriods.erase(itr);
      emit changed();
      return true;
    }
  }
  return false;
}

bool Community::removeWorkPeriod(int index)
{
  return removeWorkPeriod(mWorkPeriods.at(index).get());
}

void Community::saveToDataStream(QDataStream &dataStream) const
{
  streamio::writeString(TYPE_ID, dataStream);
  dataStream << SAVE_VERSION;
  streamio::writeString(mName, dataStream);
  streamio::writeString(mDescription, dataStream);
  dataStream << static_cast<int32_t>(mActive);
  dataStream << static_cast<int32_t>(mBoardMembers.size());
  for (std::size_t i = 0; i < mBoardMembers.size(); i++) {
    const BoardMember * boardMember = mBoardMembers.at(i).get();
    boardMember->saveToDataStream(dataStream);
  }

  dataStream << static_cast<int32_t>(mWorkPeriods.size());
  for (std::size_t i = 0; i < mWorkPeriods.size(); i++) {
    const WorkPeriod * workPeriod = mWorkPeriods.at(i).get();
    workPeriod->saveToDataStream(dataStream);
  }
}

void Community::setActive(bool value)
{
  mActive = value;
  emit changed();
}

void Community::setDescription(const QString &description)
{
  mDescription = description;
}

void Community::setName(const QString &name)
{
  mName = name;
  emit changed();
}

void Community::startWork()
{
  if (mWorking)
    return;

  mCurrentWorkPeriod.reset(new WorkPeriod);
  mCurrentWorkPeriod->setStart(QDateTime::currentDateTime());
  mTimer.start();
  mWorking = true;
  emit workStatusChanged(mWorking);
}

void Community::stopWork()
{
  if (!mWorking)
    return;

  mTimer.stop();
  mCurrentWorkPeriod->setEnd(QDateTime::currentDateTime());
  mWorkPeriods.push_back(std::move(mCurrentWorkPeriod));
  mWorking = false;
  emit workStatusChanged(mWorking);
}

int Community::timeWorked(const QDate & startDate, const QDate & endDate) const
{
  int totaltimeWorked = 0;
  for (std::size_t i = 0; i < mWorkPeriods.size(); i++) {
    const WorkPeriod * workPeriod = mWorkPeriods.at(i).get();

    QDate workStart = workPeriod->start().date();
    QDate workEnd = workPeriod->end().date();
    if (workStart >= startDate && workEnd <= endDate)
      totaltimeWorked += workPeriod->duration();
  }

  if (mCurrentWorkPeriod != nullptr) {
    totaltimeWorked += mCurrentWorkPeriod->duration();
  }

  return totaltimeWorked;
}

int Community::timeWorkedToday() const
{
  QDate date = QDate::currentDate();
  return timeWorked(date, date);
}

int Community::timeWorkedThisWeek() const
{
  QDate current = QDate::currentDate();
  int dayOfWeek = current.dayOfWeek();
  QDate start = current.addDays(-dayOfWeek+1);
  QDate end = current.addDays(7-dayOfWeek);
  return timeWorked(start, end);
}

int Community::timeWorkedThisMonth() const
{
  QDate current = QDate::currentDate();
  QDate start(current.year(), current.month(), 1);
  QDate end(current.year(), current.month(), current.daysInMonth());
  return timeWorked(start, end);
}

int Community::totalTimeWorked() const
{
  QDate start(1970, 1, 1);
  QDate end = QDate::currentDate();
  return timeWorked(start, end);
}

std::size_t Community::totalBoardMembers() const
{
  return mBoardMembers.size();
}

std::size_t Community::totalWorkPeriods() const
{
  return mWorkPeriods.size();
}

void Community::updateWorkPeriod()
{
  mCurrentWorkPeriod->setEnd(QDateTime::currentDateTime());
  emit changed();
}

bool Community::working() const
{
  return mWorking;
}
