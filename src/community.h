#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <QObject>
#include <QString>
#include <QTimer>

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

class WorkPeriod;

class Community
    : public QObject
{
  Q_OBJECT

public:
  enum class TimePeriod
  {
    Today = 0,
    ThisWeek = 1,
    LastWeek = 2,
    ThisMonth = 3,
    LastMonth = 4
  };

public:
  Community();
  ~Community();

public:
  bool active() const;
  QString name() const;
  bool working() const;
  void setActive(bool value);
  void setName(const QString & name);

public:
  void addWorkPeriod(std::unique_ptr<WorkPeriod> workPeriod);
  WorkPeriod * getWorkPeriod(std::size_t index);
  const WorkPeriod * getWorkPeriod(std::size_t index) const;
  void startWork();
  void stopWork();
  int timeWorkedToday() const;
  std::size_t totalWorkPeriods() const;
  int totalTimeWorked() const;

private slots:
  void updateWorkPeriod();

signals:
  void changed();
  void workStatusChanged(bool working);

private:
  using WorkPeriodPtr = std::unique_ptr<WorkPeriod>;
  using WorkPeriodVector = std::vector<WorkPeriodPtr>;

private:
  bool mActive;
  bool mWorking;
  QString mName;
  WorkPeriodPtr mCurrentWorkPeriod;
  WorkPeriodVector mWorkPeriods;
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
