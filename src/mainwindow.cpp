#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "community.h"
#include "communitydialog.h"
#include "communitymodel.h"
#include "overviewtabmodel.h"
#include "project.h"
#include "workperiod.h"
#include "workperioddialog.h"

#include <chrono>
#include <sstream>
#include <thread>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , mUi(new Ui::MainWindow)
  , mFileName("jeff.tta")
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
  int response = dialog.exec();
  if (response == QDialog::Rejected) {
    return;
  }

  QString name = dialog.name();
  std::unique_ptr<Community> community(new Community);
  community->setName(name);
  community->setDescription(dialog.description());
  for (std::size_t i = 0; i < dialog.totalBoardMembers(); i++) {
    BoardMember boardMember = dialog.getBoardMember(i);
    std::unique_ptr<BoardMember> newBoardMember(new BoardMember(boardMember));
    community->addBoardMember(std::move(newBoardMember));
  }

  mProject->addCommunity(std::move(community));
}

void MainWindow::handleAddWorkPeriod()
{
  WorkPeriodDialog dialog(this);
  for (std::size_t i = 0; i < mProject->totalCommunities(); i++) {
    Community * community = mProject->getCommunity(i);
    dialog.addCommunity(community);
  }

  int response = dialog.exec();
  if (response == QDialog::Rejected) {
    return;
  }
}

void MainWindow::closeEvent(QCloseEvent *)
{
  stopAllWork();
  mProject->saveToFile(mFileName);
}

void MainWindow::handleExit()
{
  stopAllWork();
  mProject->saveToFile(mFileName);
  QApplication::quit();
}

void MainWindow::handleOpenProject()
{
  openProject(mFileName);
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

  QTableView * tableView = new QTableView(mUi->cTabWidget);
  tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  CommunityModel * model = new CommunityModel;
  model->setCommunity(community);
  tableView->setModel(model);
  int index = mUi->cTabWidget->addTab(tableView, community->name());
  mUi->cTabWidget->setCurrentIndex(index);
  mTabTable[community] = tableView;
}

void MainWindow::initActions()
{
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
  mUi->cTabWidget->removeTab(1);
}

void MainWindow::newProject()
{
  mProject.reset(new Project);

  mOverviewTabModel.reset(new OverviewTabModel);
  mOverviewTabModel->setProject(mProject.get());
  mUi->cCommunitiesView->setModel(mOverviewTabModel.get());

  connect(mProject.get(), SIGNAL(modified(bool)), SLOT(handleProjectModified(bool)));
  connect(mUi->cCommunitiesView, SIGNAL(showCommunity(Community*)), SLOT(handleShowCommunityTab(Community*)));

  updateWindowTitle();
}

void MainWindow::openProject(const QString & fileName)
{
  newProject();
  mProject->loadFromFile(fileName);
  mFileName = fileName;
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
  std::ostringstream oss;
  oss << "Community Time Tracker - ";
  oss << mFileName.toStdString();
  setWindowTitle(QString::fromStdString(oss.str()));
}
