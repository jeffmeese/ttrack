#include "boardmemberdialog.h"
#include "ui_boardmemberdialog.h"

BoardMemberDialog::BoardMemberDialog(QWidget *parent)
  : QDialog(parent)
  , mUi(new Ui::BoardMemberDialog)
{
  mUi->setupUi(this);
}

BoardMemberDialog::~BoardMemberDialog()
{
  delete mUi;
}

QString BoardMemberDialog::emailAddress() const
{
  return mUi->cEmail->text().trimmed();
}

QString BoardMemberDialog::name() const
{
  return mUi->cName->text().trimmed();
}

QString BoardMemberDialog::phoneNumber() const
{
  return mUi->cPhone->text().trimmed();
}

void BoardMemberDialog::setEmailAddress(const QString & value)
{
  mUi->cEmail->setText(value);
}

void BoardMemberDialog::setName(const QString & value)
{
  mUi->cName->setText(value);
}

void BoardMemberDialog::setPhoneNumber(const QString & value)
{
  mUi->cPhone->setText(value);
}

void BoardMemberDialog::setTitle(const QString & value)
{
  mUi->cTitle->setText(value);
}

QString BoardMemberDialog::title() const
{
  return mUi->cTitle->text().trimmed();
}
