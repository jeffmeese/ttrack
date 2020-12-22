#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "community.h"
#include "communitydialog.h"
#include "communitymodel.h"
#include "overviewtabmodel.h"
#include "communityview.h"
#include "project.h"
#include "workperiod.h"
#include "workperioddialog.h"

#include <chrono>
#include <sstream>
#include <thread>

#include <QDebug>
#include <QFileDialog>

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
  CommunityDialog dialog(this);
  dialog.setActive(true);
  int response = dialog.exec();
  if (response == QDialog::Rejected) {
    return;
  }

  QString name = dialog.name();
  std::unique_ptr<Community> community(new Community);
  community->setName(name);
  community->setDescription(dialog.description());
  for (int i = 0; i < dialog.totalBoardMembers(); i++) {
    BoardMember boardMember = dialog.getBoardMember(i);
    std::unique_ptr<BoardMember> newBoardMember(new BoardMember(boardMember));
    community->addBoardMember(std::move(newBoardMember));
  }
  mProject->addCommunity(std::move(community));
}

void MainWindow::handleAddWorkPeriod()
{
  WorkPeriodDialog dialog(this);
  dialog.setStart(QDateTime(QDate::currentDate(), QTime::currentTime()));
  dialog.setEnd(QDateTime(QDate::currentDate(), QTime::currentTime()));
  for (std::size_t i = 0; i < mProject->totalCommunities(); i++) {
    Community * community = mProject->getCommunity(i);
    dialog.addCommunity(community);
  }

  int response = dialog.exec();
  if (response == QDialog::Rejected) {
    return;
  }

  Community * community = dialog.community();
  QDateTime start = dialog.startTime();
  QDateTime end = dialog.endTime();

  std::unique_ptr<WorkPeriod> workPeriod(new WorkPeriod(start, end));
  workPeriod->setNotes(dialog.notes());
  community->addWorkPeriod(std::move(workPeriod));

  mProject->saveToFile(mFileName);
}

void MainWindow::closeEvent(QCloseEvent *)
{
  stopAllWork();
  if (!mFileName.isEmpty())
    mProject->saveToFile(mFileName);
}

void MainWindow::handleAboutToShowCommunities()
{
  mUi->actionAdd_Community->setEnabled(!mFileName.isEmpty());
  mUi->actionAdd_Work_Period->setEnabled(!mFileName.isEmpty());
}

void MainWindow::handleAboutToShowProgram()
{
  mUi->actionSave_Project_As->setEnabled(!mFileName.isEmpty());
}


void MainWindow::handleExit()
{
  stopAllWork();
  if (!mFileName.isEmpty())
    mProject->saveToFile(mFileName);

  QApplication::quit();
}

void MainWindow::handleOpenProject()
{
  QString caption("Choose a file");
  QString filter("Community Time Tracker Files (*.tta)");
  QString fileName = QFileDialog::getOpenFileName(this, caption, QDir::currentPath(), filter);
  if (fileName.isEmpty())
    return;

  openProject(fileName);
}

void MainWindow::handleOptions()
{

}

void MainWindow::handleProjectModified(bool)
{
  mProject->saveToFile(mFileName);
}

void MainWindow::handleNewProject()
{
  QString caption("Enter a file name");
  QString filter("Community Time Tracker Files (*.tta)");
  QString fileName = QFileDialog::getSaveFileName(this, caption, QDir::currentPath(), filter);
  qDebug() << fileName;
  if (fileName.isEmpty())
    return;

  mFileName = fileName;
  newProject();
}

void MainWindow::handleSaveProjectAs()
{
  saveProject(mFileName);
}

void MainWindow::handleShowCommunityTab(Community * community)
{
  TabWidgetTable::iterator itr = mTabTable.find(community);
  if (itr != mTabTable.end()) {
    for (int i = 0; i < mUi->cTabWidget->count(); i++) {
      QWidget * widget = mUi->cTabWidget->widget(i);
      if (itr->second == widget) {
        mUi->cTabWidget->setCurrentIndex(i);
        return;
      }
    }
  }

  CommunityView * tableView = new CommunityView(mUi->cTabWidget);
  tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  CommunityModel * model = new CommunityModel;
  model->setCommunity(community);
  tableView->setModel(model);
  int index = mUi->cTabWidget->addTab(tableView, community->name());
  mUi->cTabWidget->setCurrentIndex(index);
  mTabTable[community] = tableView;
}

void MainWindow::handleTabClosed(int index)
{
  qDebug() << QObject::tr(__FUNCTION__);

  QWidget * widget = mUi->cTabWidget->widget(index);
  if (widget == mUi->cCommunitiesView) {
    // Can't close the overview tab
    return;
  }

  for (TabWidgetTable::iterator itr = mTabTable.begin(); itr != mTabTable.end(); itr++) {
    if (itr->second == widget) {
      mUi->cTabWidget->removeTab(index);
      mTabTable.erase(itr);
      delete widget;
    }
  }
}

void MainWindow::initActions()
{
  connect(mUi->menuProgram, SIGNAL(aboutToShow()), SLOT(handleAboutToShowProgram()));
  connect(mUi->menuProject, SIGNAL(aboutToShow()), SLOT(handleAboutToShowCommunities()));

  connect(mUi->actionNew_Project, SIGNAL(triggered()), SLOT(handleNewProject()));
  connect(mUi->actionOpen_Project, SIGNAL(triggered()), SLOT(handleOpenProject()));
  connect(mUi->actionSave_Project_As, SIGNAL(triggered()), SLOT(handleSaveProjectAs()));
  connect(mUi->actionOptions, SIGNAL(triggered()), SLOT(handleOptions()));
  connect(mUi->actionExit, SIGNAL(triggered()), SLOT(handleExit()));
  connect(mUi->actionAdd_Community, SIGNAL(triggered()), SLOT(handleAddCommunity()));
  connect(mUi->actionAdd_Work_Period, SIGNAL(triggered()), SLOT(handleAddWorkPeriod()));
}

void MainWindow::initUi()
{
  mUi->setupUi(this);
  mUi->cFilter->addItem("All Communities");
  mUi->cFilter->addItem("Active Communities");
}

void MainWindow::newProject()
{
  mProject.reset(new Project);

  mOverviewTabModel.reset(new OverviewTabModel);
  mOverviewTabModel->setProject(mProject.get());
  mUi->cCommunitiesView->setModel(mOverviewTabModel.get());

  connect(mProject.get(), SIGNAL(modified(bool)), SLOT(handleProjectModified(bool)));
  connect(mUi->cCommunitiesView, SIGNAL(showCommunity(Community*)), SLOT(handleShowCommunityTab(Community*)));
  connect(mUi->cTabWidget, SIGNAL(tabCloseRequested(int)), SLOT(handleTabClosed(int)));

  updateWindowTitle();
}

void MainWindow::openProject(const QString & fileName)
{
  newProject();
  mProject->loadFromFile(fileName);
  mFileName = fileName;
  mOverviewTabModel->setProject(mProject.get());
  updateWindowTitle();
}

void MainWindow::saveProject(const QString & fileName)
{
  mProject->saveToFile(fileName);
  mFileName = fileName;
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

void MainWindow::updateWindowTitle()
{
  QFileInfo fileInfo(mFileName);

  std::ostringstream oss;
  oss << "Community Time Tracker - ";
  oss << fileInfo.fileName().toStdString();
  setWindowTitle(QString::fromStdString(oss.str()));
}
