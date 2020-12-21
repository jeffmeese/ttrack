#include "workperioddialog.h"
#include "ui_workperioddialog.h"

#include "community.h"
#include "workperiod.h"

Q_DECLARE_METATYPE(Community*);

WorkPeriodDialog::WorkPeriodDialog(QWidget *parent)
  : QDialog(parent)
  , mUi(new Ui::WorkPeriodDialog)
{
  mUi->setupUi(this);
  updateData();
}

WorkPeriodDialog::~WorkPeriodDialog()
{
  delete mUi;
}

void WorkPeriodDialog::addCommunity(Community *community)
{
  QVariant v;
  v.setValue(community);
  mUi->cCommunity->addItem(community->name(), v);
  mUi->cCommunity->setCurrentIndex(-1);
}

void WorkPeriodDialog::setCommunity(Community *community)
{
  for (int i = 0; i < mUi->cCommunity->count(); i++) {
    QVariant v = mUi->cCommunity->itemData(i);
    Community * c = v.value<Community*>();
    if (c == community) {
      mUi->cCommunity->setCurrentIndex(i);
      return;
    }
  }
}

void WorkPeriodDialog::setEnableCommunity(bool enable)
{
  mUi->cCommunity->setEnabled(enable);
}

void WorkPeriodDialog::setEnd(const QDateTime &dateTime)
{
  mUi->cEndTime->setDateTime(dateTime);
}

void WorkPeriodDialog::setStart(const QDateTime &dateTime)
{
  mUi->cStartTime->setDateTime(dateTime);
}

void WorkPeriodDialog::updateData()
{

}
