#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <QObject>
#include <QString>
#include <QTimer>

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

class BoardMember;
class WorkPeriod;

class Community
    : public QObject
{
  Q_OBJECT

public:
  Community();
  ~Community();

public:
  bool active() const;
  QString description() const;
  QString name() const;
  bool working() const;
  void setActive(bool value);
  void setDescription(const QString & description);
  void setName(const QString & name);

public:
  void addBoardMember(std::unique_ptr<BoardMember> boardMember);
  void addWorkPeriod(std::unique_ptr<WorkPeriod> workPeriod);
  BoardMember * getBoardMember(std::size_t index);
  const BoardMember * getBoardMember(std::size_t index) const;
  WorkPeriod * getWorkPeriod(std::size_t index);
  const WorkPeriod * getWorkPeriod(std::size_t index) const;
  void loadFromDataStream(QDataStream & dataStream);
  void removeAllBoardMembers();
  bool removeWorkPeriod(WorkPeriod * workPeriod);
  bool removeWorkPeriod(int index);
  void saveToDataStream(QDataStream & dataStream) const;
  void startWork();
  void stopWork();
  int timeWorked(const QDate & startDate, const QDate & endDate) const;
  int timeWorkedToday() const;
  int timeWorkedThisWeek() const;
  int timeWorkedThisMonth() const;
  int totalTimeWorked() const;
  std::size_t totalBoardMembers() const;
  std::size_t totalWorkPeriods() const;

private slots:
  void updateWorkPeriod();

signals:
  void changed();
  void workStatusChanged(bool working);

private:
  using WorkPeriodPtr = std::unique_ptr<WorkPeriod>;
  using WorkPeriodVector = std::vector<WorkPeriodPtr>;
  using BoardMemberPtr = std::unique_ptr<BoardMember>;
  using BoardMemberVector = std::vector<BoardMemberPtr>;

private:
  bool mActive;
  bool mWorking;
  QString mDescription;
  QString mName;
  BoardMemberVector mBoardMembers;
  WorkPeriodPtr mCurrentWorkPeriod;
  WorkPeriodVector mWorkPeriods;
  QTimer mTimer;
};

#endif // COMMUNITY_H
