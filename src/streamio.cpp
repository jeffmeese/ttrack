#include "streamio.h"

QString streamio::readString(QDataStream & dataStream)
{
  QString s;
  int32_t length;
  dataStream >> length;
  if (length > 0) {
    char * value = new char[length];
    dataStream.readRawData(value, length);
    s = value;
    delete [] value;
  }
  return s;
}

void streamio::writeString(const QString & s, QDataStream & dataStream)
{
  dataStream << static_cast<int32_t>(s.length());
  if (s.length() > 0)
    dataStream.writeRawData(s.toStdString().c_str(), s.length());
}
