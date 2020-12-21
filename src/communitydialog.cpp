#include "communitydialog.h"
#include "ui_communitydialog.h"

#include "boardmemberdialog.h"

CommunityDialog::CommunityDialog(QWidget *parent)
  : QDialog(parent)
  , mUi(new Ui::CommunityDialog)
{
  mUi->setupUi(this);
  mUi->cBoardMembers->setColumnCount(4);
  QTableWidgetItem * nameItem = new QTableWidgetItem("Name");
  QTableWidgetItem * titleItem = new QTableWidgetItem("Title");
  QTableWidgetItem * phoneItem = new QTableWidgetItem("Phone Number");
  QTableWidgetItem * emailItem = new QTableWidgetItem("Email Address");

  mUi->cBoardMembers->setHorizontalHeaderItem(0, nameItem);
  mUi->cBoardMembers->setHorizontalHeaderItem(1, titleItem);
  mUi->cBoardMembers->setHorizontalHeaderItem(2, phoneItem);
  mUi->cBoardMembers->setHorizontalHeaderItem(3, emailItem);
  mUi->cBoardMembers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  connect(mUi->cName, SIGNAL(textChanged(QString)), SLOT(updateData()));
  connect(mUi->cAddMember, SIGNAL(clicked()), SLOT(handleAddMember()));
  updateData();
}

CommunityDialog::~CommunityDialog()
{
  delete mUi;
}

void CommunityDialog::addBoardMember(const BoardMember & boardMember)
{
  int rows = mUi->cBoardMembers->rowCount();
  mUi->cBoardMembers->setRowCount(mUi->cBoardMembers->rowCount()+1);
  QTableWidgetItem * nameItem = new QTableWidgetItem(boardMember.name());
  QTableWidgetItem * titleItem = new QTableWidgetItem(boardMember.title());
  QTableWidgetItem * phoneItem = new QTableWidgetItem(boardMember.phoneNumber());
  QTableWidgetItem * emailItem = new QTableWidgetItem(boardMember.emailAddress());

  mUi->cBoardMembers->setItem(rows, 0, nameItem);
  mUi->cBoardMembers->setItem(rows, 1, titleItem);
  mUi->cBoardMembers->setItem(rows, 2, phoneItem);
  mUi->cBoardMembers->setItem(rows, 3, emailItem);

  mBoardMembers.push_back(boardMember);
}

BoardMember CommunityDialog::getBoardMember(int index)
{
  return mBoardMembers.at(index);
}

void CommunityDialog::accept()
{
  QDialog::accept();
}

QString CommunityDialog::description() const
{
  return mUi->cDescription->text().trimmed();
}

void CommunityDialog::handleAddMember()
{
  BoardMemberDialog dialog(this);
  int response = dialog.exec();
  if (response == QDialog::Rejected)
    return;

  BoardMember boardMember;
  boardMember.setEmailAddress(dialog.emailAddress());
  boardMember.setName(dialog.name());
  boardMember.setPhoneNumber(dialog.phoneNumber());
  boardMember.setTitle(dialog.title());

  addBoardMember(boardMember);
}

void CommunityDialog::handleRemoveMember()
{

}

QString CommunityDialog::name() const
{
  return mUi->cName->text().trimmed();
}

void CommunityDialog::setDescription(const QString &description)
{
  mUi->cDescription->setText(description);
}

void CommunityDialog::setName(const QString &name)
{
  mUi->cName->setText(name);
}

int CommunityDialog::totalBoardMembers() const
{
  return static_cast<int>(mBoardMembers.size());
}

void CommunityDialog::updateData()
{
  bool enableOk = true;
  QString name = mUi->cName->text().trimmed();
  if (name.isEmpty())
    enableOk = false;

  mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enableOk);
}
