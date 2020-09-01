#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <QObject>
#include <QString>
#include <QTimer>

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

class Community
    : public QObject
{
  Q_OBJECT

public:
  Community();

public:
  QString name() const;
  bool working() const;
  void setName(const QString & name);

public:
  void startWork();
  void stopWork();
  int totalTimeWorked() const;

private slots:
  void updateWorkTime();

signals:
  void workTimeIncrement();

private:
  struct WorkTime
  {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point stop;
  };

private:
  bool mWorking;
  QString mName;
  WorkTime mCurrentWork;
  std::vector<WorkTime> mTimeWorked;
  QTimer mTimer;
};

inline QString Community::name() const
{
  return mName;
}

inline bool Community::working() const
{
  return mWorking;
}

inline void Community::setName(const QString &name)
{
  mName = name;
}

#endif // COMMUNITY_H
