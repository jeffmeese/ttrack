#ifndef COMMUNITYDIALOG_H
#define COMMUNITYDIALOG_H

#include <QDialog>

#include "boardmember.h"

namespace Ui {
class CommunityDialog;
}

class CommunityDialog : public QDialog
{
  Q_OBJECT

public:
  explicit CommunityDialog(QWidget *parent = nullptr);
  ~CommunityDialog();

public:
  bool active() const;
  QString description() const;
  QString name() const;
  void setActive(bool active);
  void setDescription(const QString & description);
  void setName(const QString & name);

public:
  void addBoardMember(const BoardMember & boardMember);
  BoardMember getBoardMember(int index);
  int totalBoardMembers() const;

private slots:
  void accept() override;
  void handleAddMember();
  void handleRemoveMember();
  void updateData();

private:
  Ui::CommunityDialog * mUi;
  std::vector<BoardMember> mBoardMembers;
};

#endif // COMMUNITYDIALOG_H
