#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <memory>

class Community;
class OverviewTabModel;
class Project;
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent * event) override;

private slots:
  void handleAddCommunity();
  void handleAddWorkPeriod();
  void handleAboutToShowProgram();
  void handleAboutToShowCommunities();
  void handleExit();
  void handleNewProject();
  void handleOpenProject();
  void handleOptions();
  void handleProjectModified(bool modified);
  void handleSaveProjectAs();
  void handleShowCommunityTab(Community * community);
  void handleTabClosed(int index);

private:
  void initActions();
  void initUi();
  void newProject();
  void openProject(const QString & fileName);
  void saveProject(const QString & fileName);
  void stopAllWork();
  void updateWindowTitle();

private:
  enum DateFilter
  {
    Today = 0,
    Yesterday = 1,
    ThisMonth = 2,
    LastMonth = 3,
    ThisYear = 4,
    LastYear = 5,
    Custom = 6
  };

  enum CommunityFilter
  {
    All = 0,
    Active = 1,
  };

private:
  using TabWidgetTable = std::map<Community*, QWidget*>;

private:
  std::unique_ptr<Ui::MainWindow> mUi;
  std::unique_ptr<Project> mProject;
  std::unique_ptr<OverviewTabModel> mOverviewTabModel;
  TabWidgetTable mTabTable;
  QString mFileName;
};
#endif // MAINWINDOW_H
