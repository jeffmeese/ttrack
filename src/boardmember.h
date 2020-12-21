#ifndef BOARDMEMBER_H
#define BOARDMEMBER_H

#include <QString>

class BoardMember
{
public:
  BoardMember();

public:
  QString emailAddress() const;
  QString name() const;
  QString phoneNumber() const;
  QString title() const;
  void setEmailAddress(const QString & value);
  void setName(const QString & name);
  void setPhoneNumber(const QString & value);
  void setTitle(const QString & value);

public:
  void loadFromDataStream(QDataStream & dataStream);
  void saveToDataStream(QDataStream & dataStream) const;

private:
  QString mEmailAddress;
  QString mName;
  QString mPhoneNumber;
  QString mTitle;
};

#endif // BOARDMEMBER_H
