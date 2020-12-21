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
  void addCommunity(Community * community);
  void setCommunity(Community * community);
  void setEnableCommunity(bool enable);
  void setStart(const QDateTime & dateTime);
  void setEnd(const QDateTime & dateTime);

private slots:
  void updateData();

private:
  Ui::WorkPeriodDialog *mUi;
};

#endif // WORKPERIODDIALOG_H
