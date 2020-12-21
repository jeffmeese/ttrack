#ifndef STREAMIO_H
#define STREAMIO_H

#include <QDataStream>
#include <QString>

namespace streamio
{
  QString readString(QDataStream & dataStream);
  void writeString(const QString & s, QDataStream & dataStream);
}

#endif // STREAMIO_H
