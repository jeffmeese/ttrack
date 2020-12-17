#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <memory>

class Community;
class Project;
class ProjectModel;
class ReportModel;
class Switch;
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
  void handleExit();
  void handleNewProject();
  void handleOpenProject();
  void handleOptions();
  void handleSaveProject();
  void handleSaveProjectAs();
  void handleSliderClick();
  void handleUpdate();
  void updateTimeControls();

private:
  void addCommunity(Community * community);
  void initActions();
  void initUi();
  void newProject();
  void stopAllWork();

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
  std::unique_ptr<Ui::MainWindow> mUi;
  std::unique_ptr<Project> mProject;
  std::unique_ptr<ProjectModel> mProjectModel;
  std::unique_ptr<ReportModel> mReportModel;
  std::map<Switch*, Community*> mSwitchMap;
  QTimer mUpdateTimer;
};
#endif // MAINWINDOW_H
