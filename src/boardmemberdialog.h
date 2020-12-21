#ifndef BOARDMEMBERDIALOG_H
#define BOARDMEMBERDIALOG_H

#include <QDialog>

namespace Ui {
class BoardMemberDialog;
}

class BoardMemberDialog : public QDialog
{
  Q_OBJECT

public:
  explicit BoardMemberDialog(QWidget *parent = nullptr);
  ~BoardMemberDialog();

public:
  QString emailAddress() const;
  QString name() const;
  QString phoneNumber() const;
  QString title() const;
  void setEmailAddress(const QString & value);
  void setName(const QString & name);
  void setPhoneNumber(const QString & value);
  void setTitle(const QString & value);

private:
  Ui::BoardMemberDialog *mUi;
};

#endif // BOARDMEMBERDIALOG_H
