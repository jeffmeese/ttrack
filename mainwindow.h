#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <memory>

class Community;
class Project;
class ProjectModel;
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

private:
  void initActions();
  void initUi();
  void newProject();

private:
  std::unique_ptr<Ui::MainWindow> mUi;
  std::unique_ptr<Project> mProject;
  std::unique_ptr<ProjectModel> mModel;
  std::map<Switch*, Community*> mSwitchMap;
  QTimer mUpdateTimer;
};
#endif // MAINWINDOW_H
