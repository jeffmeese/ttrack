cmake_minimum_required(VERSION 3.5)

project(ttrack LANGUAGES CXX)

set(HDR_FILES
  boardmember.h
  boardmemberdialog.h
  community.h
  communitydialog.h
  communitymodel.h
  communityview.h
  mainwindow.h
  overviewtabdelegate.h
  overviewtabmodel.h
  overviewtabview.h
  project.h
  streamio.h
  workperiod.h
  workperioddialog.h
)

set(SRC_FILES
  boardmember.cpp
  boardmemberdialog.cpp
  community.cpp
  communitydialog.cpp
  communitymodel.cpp
  communityview.cpp
  mainwindow.cpp
  main.cpp
  overviewtabdelegate.cpp
  overviewtabmodel.cpp
  overviewtabview.cpp
  project.cpp
  streamio.cpp
  workperiod.cpp
  workperioddialog.cpp
)

set(UI_FILES
  boardmemberdialog.ui
  communitydialog.ui
  mainwindow.ui
  workperioddialog.ui
)

add_executable(ttrack ${HDR_FILES} ${SRC_FILES} ${UI_FILES})

target_link_libraries(ttrack PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
