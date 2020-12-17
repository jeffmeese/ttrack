#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "community.h"
#include "project.h"
#include "projectmodel.h"
#include "switch.h"

#include <chrono>
#include <thread>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , mUi(new Ui::MainWindow)
{
  initUi();
  initActions();
  newProject();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleAddCommunity()
{
  std::size_t totalCommunities = mProject->totalCommunities();
  QString name = "Community " + QString::number(totalCommunities + 1);
  std::unique_ptr<Community> community(new Community);
  community->setName(name);

  Switch * sw = new Switch;
  mSwitchMap.insert(std::make_pair(sw, community.get()));
  mProject->addCommunity(std::move(community));

  mUi->cProjectView->setIndexWidget(mModel->index(totalCommunities, 0), sw);
  connect(sw, SIGNAL(clicked()), SLOT(handleSliderClick()));
}

void MainWindow::handleAddWorkPeriod()
{

}

void MainWindow::handleExit()
{
  QApplication::quit();
}

void MainWindow::handleOpenProject()
{

}

void MainWindow::handleOptions()
{

}

void MainWindow::handleNewProject()
{

}

void MainWindow::handleSaveProject()
{

}

void MainWindow::handleSaveProjectAs()
{

}

void MainWindow::handleSliderClick()
{
  Switch * s = (Switch*)sender();
  auto itr = mSwitchMap.find(s);
  if (itr != mSwitchMap.end()) {
    Community * c = itr->second;
    if (c->working()) {
      c->stopWork();
      mUpdateTimer.stop();
    }
    else {
      for (auto itr2 = mSwitchMap.begin(); itr2 != mSwitchMap.end(); ++itr2) {
        Community * c2 = itr2->second;
        Switch * s2 = itr2->first;
        if (c2 != c) {
          c2->stopWork();
          s2->setOn(false);
        }
      }
      c->startWork();
      mUpdateTimer.start();
    }
  }
}

void MainWindow::handleUpdate()
{
  mUi->cProjectView->update();
}

void MainWindow::initActions()
{
  connect(mUi->actionNew_Project, SIGNAL(triggered()), SLOT(handleNewProject()));
  connect(mUi->actionOpen_Project, SIGNAL(triggered()), SLOT(handleOpenProject()));
  connect(mUi->actionSave_Project, SIGNAL(triggered()), SLOT(handleSaveProject()));
  connect(mUi->actionSave_Project_As, SIGNAL(triggered()), SLOT(handleSaveProjectAs()));
  connect(mUi->actionOptions, SIGNAL(triggered()), SLOT(handleOptions()));
  connect(mUi->actionExit, SIGNAL(triggered()), SLOT(handleExit()));

  connect(mUi->actionAdd_Community, SIGNAL(triggered()), SLOT(handleAddCommunity()));
  connect(mUi->actionAdd_Work_Period, SIGNAL(triggered()), SLOT(handleAddWorkPeriod()));
}

void MainWindow::initUi()
{
  mUi->setupUi(this);

  mUi->cDateRange->addItem("Today");
  mUi->cDateRange->addItem("Yesterday");
  mUi->cDateRange->addItem("This Month");
  mUi->cDateRange->addItem("Last Month");
  mUi->cDateRange->addItem("This Year");
  mUi->cDateRange->addItem("Last Year");
  mUi->cDateRange->addItem("Custom");

  mUi->cFilter->addItem("All Communities");
  mUi->cFilter->addItem("Active Communities");

  mUpdateTimer.setInterval(1000);
  connect(&mUpdateTimer, SIGNAL(timeout()), SLOT(handleUpdate()));
}

void MainWindow::newProject()
{
  mProject.reset(new Project);

  mModel.reset(new ProjectModel);
  mModel->setProject(mProject.get());
  mUi->cProjectView->setModel(mModel.get());
}
