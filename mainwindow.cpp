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
  mUi->setupUi(this);

  mUpdateTimer.setInterval(1000);
  mUpdateTimer.stop();
  connect(&mUpdateTimer, SIGNAL(timeout()), SLOT(handleUpdate()));

  mUi->cDateRange->addItem("Today");
  mUi->cDateRange->addItem("Yesterday");
  mUi->cDateRange->addItem("This Month");
  mUi->cDateRange->addItem("Last Month");
  mUi->cDateRange->addItem("This Year");
  mUi->cDateRange->addItem("Last Year");
  mUi->cDateRange->addItem("Custom");

  mUi->cFilter->addItem("All Communities");
  mUi->cFilter->addItem("Active Communities");

  mProject.reset(new Project);

  mModel.reset(new ProjectModel);
  mModel->setProject(mProject.get());
  mUi->cProjectView->setModel(mModel.get());

  handleAddCommunity();
  handleAddCommunity();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleAddCommunity()
{
  int totalCommunities = mProject->totalCommunities();
  QString name = "Community " + QString::number(totalCommunities + 1);
  std::unique_ptr<Community> community(new Community);
  community->setName(name);

  Switch * sw = new Switch;
  mSwitchMap.insert(std::make_pair(sw, community.get()));
  connect(community.get(), SIGNAL(workTimeIncrement()), mModel.get(), SLOT(handleCommunityUpdate()));
  mProject->addCommunity(std::move(community));

  mUi->cProjectView->setIndexWidget(mModel->index(totalCommunities, 0), sw);
  connect(sw, SIGNAL(clicked()), SLOT(handleSliderClick()));
}

void MainWindow::handleSliderClick()
{
  Switch * s = (Switch*)sender();
  std::map<Switch*, Community*>::iterator itr = mSwitchMap.find(s);
  if (itr != mSwitchMap.end()) {
    Community * c = itr->second;
    if (c->working()) {
      c->stopWork();
      mUpdateTimer.stop();
    }
    else {
      for (std::size_t i = 0; i < mProject->totalCommunities(); i++) {
        Community * c2 = mProject->getCommunity(i);
        if (c2 != c) {
          c2->stopWork();
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
