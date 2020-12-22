#include "streamio.h"

QString streamio::readString(QDataStream & dataStream)
{
  QString s;
  if (dataStream.atEnd()) {
    return s;
  }

  uint32_t length = readUInt32(dataStream);
  if (length > 0) {
    char * value;
    dataStream.readBytes(value, length);
    s = value;
    delete [] value;
  }
  return s;
}

int8_t streamio::readInt8(QDataStream & dataStream)
{
  int8_t value = 0;
  dataStream >> value;
  return value;
}

int16_t streamio::readInt16(QDataStream & dataStream)
{
  int16_t value = 0;
  dataStream >> value;
  return value;
}

int32_t streamio::readInt32(QDataStream & dataStream)
{
  int32_t value = 0;
  dataStream >> value;
  return value;
}

uint8_t streamio::readUInt8(QDataStream & dataStream)
{
  uint8_t value = 0;
  dataStream >> value;
  return value;
}

uint16_t streamio::readUInt16(QDataStream & dataStream)
{
  uint16_t value = 0;
  dataStream >> value;
  return value;
}

uint32_t streamio::readUInt32(QDataStream & dataStream)
{
  uint32_t value = 0;
  dataStream >> value;
  return value;
}

void streamio::writeString(const QString & s, QDataStream & dataStream)
{
  dataStream << static_cast<uint32_t>(s.length());
  if (s.length() > 0)
    dataStream.writeBytes(s.toStdString().c_str(), s.length());
}
