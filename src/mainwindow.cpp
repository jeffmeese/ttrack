#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "community.h"
#include "communitymodel.h"
#include "project.h"
#include "reportmodel.h"
#include "switch.h"
#include "workperiod.h"

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
  updateTimeControls();
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
  mProject->addCommunity(std::move(community));
}

void MainWindow::handleAddWorkPeriod()
{

}

void MainWindow::closeEvent(QCloseEvent * event)
{
  qDebug() << QObject::tr(__FUNCTION__);
  stopAllWork();
}

void MainWindow::handleExit()
{
  stopAllWork();
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

void MainWindow::handleUpdate()
{
  mUi->cCommunitiesView->update();
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

  mUi->cStartTime->setEnabled(false);
  mUi->cEndTime->setEnabled(false);

  mUi->cDateRange->addItem("Today", QVariant(DateFilter::Today));
  mUi->cDateRange->addItem("Yesterday", QVariant(DateFilter::Yesterday));
  mUi->cDateRange->addItem("This Month", QVariant(DateFilter::ThisMonth));
  mUi->cDateRange->addItem("Last Month", QVariant(DateFilter::LastMonth));
  mUi->cDateRange->addItem("This Year", QVariant(DateFilter::ThisYear));
  mUi->cDateRange->addItem("Last Year", QVariant(DateFilter::LastYear));
  mUi->cDateRange->addItem("Custom", QVariant(DateFilter::Custom));

  mUi->cFilter->addItem("All Communities", CommunityFilter::All);
  mUi->cFilter->addItem("Active Communities", CommunityFilter::Active);
  mUi->cReports->setVisible(false);
  mUi->cTabWidget->removeTab(1);

  mUpdateTimer.setInterval(1000);
  connect(&mUpdateTimer, SIGNAL(timeout()), SLOT(handleUpdate()));
  connect(mUi->cDateRange, SIGNAL(currentIndexChanged(int)), SLOT(updateTimeControls()));
}

void MainWindow::newProject()
{
  mProject.reset(new Project);

  mCommunityModel.reset(new CommunityModel);
  mCommunityModel->setProject(mProject.get());
  mUi->cCommunitiesView->setModel(mCommunityModel.get());

  std::unique_ptr<Community> pheasantGlen(new Community);
  pheasantGlen->setName("Pheasant Glen");
  QDateTime start(QDate(2020, 12, 16), QTime(12, 25, 30));
  QDateTime end(QDate(2020, 12, 16), QTime(14, 25, 0));
  pheasantGlen->addWorkPeriod(std::unique_ptr<WorkPeriod>(new WorkPeriod(start, end)));
  mProject->addCommunity(std::move(pheasantGlen));

  std::unique_ptr<Community> countryWalk1(new Community);
  countryWalk1->setName("County Walk 1");
  start.setDate(QDate(2020, 12, 16));
  start.setTime(QTime(14, 45, 0));
  end.setDate(QDate(2020, 12, 16));
  end.setTime(QTime(15, 25, 0));
  countryWalk1->addWorkPeriod(std::unique_ptr<WorkPeriod>(new WorkPeriod(start, end)));
  mProject->addCommunity(std::move(countryWalk1));

  std::unique_ptr<Community> countryWalk3(new Community);
  countryWalk3->setName("County Walk 3");
  start.setDate(QDate(2020, 12, 17));
  start.setTime(QTime(16, 45, 0));
  end.setDate(QDate(2020, 12, 17));
  end.setTime(QTime(18, 0, 0));
  countryWalk3->addWorkPeriod(std::unique_ptr<WorkPeriod>(new WorkPeriod(start, end)));
  mProject->addCommunity(std::move(countryWalk3));
}

void MainWindow::stopAllWork()
{
  int total = mProject->totalCommunities();
  for (int i = 0; i < total; i++) {
    Community * community = mProject->getCommunity(i);
    if (community->working())
      community->stopWork();
  }
}
void MainWindow::updateTimeControls()
{
  qDebug() << QObject::tr(__FUNCTION__);
  mUi->cStartTime->setEnabled(false);
  mUi->cEndTime->setEnabled(false);

  QDate date = QDate::currentDate();
  QDate startDate = QDate::currentDate();
  QDate endDate = QDate::currentDate();

  int startHour = 0;
  int endHour = 23;
  int startMinute = 0;
  int endMinute = 59;
  int startSecond = 0;
  int endSecond = 59;

  QVariant v = mUi->cDateRange->itemData(mUi->cDateRange->currentIndex());
  int data = v.toInt();
  switch (data) {
  case DateFilter::Today:
    break;
  case DateFilter::Yesterday:
    startDate = startDate.addDays(-1);
    endDate = endDate.addDays(-1);
    break;
  case DateFilter::ThisMonth:
    startDate.setDate(startDate.year(), startDate.month(), 1);
    endDate.setDate(endDate.year(), endDate.month(), endDate.daysInMonth());
    break;
  case DateFilter::LastMonth:
    startDate = startDate.addMonths(-1);
    endDate = endDate.addMonths(-1);
    startDate.setDate(startDate.year(), startDate.month(), 1);
    endDate.setDate(endDate.year(), endDate.month(), endDate.daysInMonth());
    break;
  case DateFilter::ThisYear:
    startDate.setDate(startDate.year(), 1, 1);
    endDate.setDate(endDate.year(), 12, 31);
    break;
  case DateFilter::LastYear:
    startDate = startDate.addYears(-1);
    endDate = endDate.addYears(-1);
    startDate.setDate(startDate.year(), 1, 1);
    endDate.setDate(endDate.year(), 12, 31);
    break;
  }

  //QDate startDate(date);
  QTime startTime(startHour, startMinute, startSecond);

  //QDate endDate(date);
  QTime endTime(endHour, endMinute, endSecond);

  mUi->cStartTime->setDate(startDate);
  mUi->cStartTime->setTime(startTime);
  mUi->cEndTime->setDate(endDate);
  mUi->cEndTime->setTime(endTime);
}
