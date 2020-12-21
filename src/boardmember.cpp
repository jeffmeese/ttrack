#include "boardmember.h"
#include "streamio.h"

#include <QDataStream>

static const QString TYPE_ID("BoardMember");
static const int32_t SAVE_VERSION = 1;

BoardMember::BoardMember()
{

}

QString BoardMember::emailAddress() const
{
  return mEmailAddress;
}

QString BoardMember::name() const
{
  return mName;
}

QString BoardMember::phoneNumber() const
{
  return mPhoneNumber;
}

void BoardMember::loadFromDataStream(QDataStream &dataStream)
{
  int32_t version = 0;
  dataStream >> version;

  mName = streamio::readString(dataStream);
  mTitle = streamio::readString(dataStream);
  mPhoneNumber = streamio::readString(dataStream);
  mEmailAddress = streamio::readString(dataStream);
}

void BoardMember::saveToDataStream(QDataStream &dataStream) const
{
  streamio::writeString(TYPE_ID, dataStream);
  dataStream << SAVE_VERSION;

  streamio::writeString(mName, dataStream);
  streamio::writeString(mTitle, dataStream);
  streamio::writeString(mPhoneNumber, dataStream);
  streamio::writeString(mEmailAddress, dataStream);
}

void BoardMember::setEmailAddress(const QString & value)
{
  mEmailAddress = value;
}

void BoardMember::setName(const QString & value)
{
  mName = value;
}

void BoardMember::setPhoneNumber(const QString & value)
{
  mPhoneNumber = value;
}

void BoardMember::setTitle(const QString & value)
{
  mTitle = value;
}

QString BoardMember::title() const
{
  return mTitle;
}
