#ifndef WORKPERIODDIALOG_H
#define WORKPERIODDIALOG_H

#include <QDialog>

class Community;
namespace Ui {
class WorkPeriodDialog;
}

class WorkPeriodDialog : public QDialog
{
  Q_OBJECT

public:
  explicit WorkPeriodDialog(QWidget *parent = nullptr);
  ~WorkPeriodDialog();

public:
  Community * community();
  QDateTime endTime() const;
  QString notes() const;
  QDateTime startTime() const;
  void setEnd(const QDateTime & dateTime);
  void setNotes(const QString & notes);
  void setStart(const QDateTime & dateTime);

public:
  void addCommunity(Community * community);
  void setCommunity(Community * community);
  void setEnableCommunity(bool enable);

private slots:
  void updateData();

private:
  Ui::WorkPeriodDialog *mUi;
};

#endif // WORKPERIODDIALOG_H
