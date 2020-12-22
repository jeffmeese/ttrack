#ifndef STREAMIO_H
#define STREAMIO_H

#include <QDataStream>
#include <QString>

namespace streamio
{
  QString readString(QDataStream & dataStream);
  int8_t readInt8(QDataStream & dataStream);
  int16_t readInt16(QDataStream & dataStream);
  int32_t readInt32(QDataStream & dataStream);
  uint8_t readUInt8(QDataStream & dataStream);
  uint16_t readUInt16(QDataStream & dataStream);
  uint32_t readUInt32(QDataStream & dataStream);
  void writeString(const QString & s, QDataStream & dataStream);
}

#endif // STREAMIO_H
