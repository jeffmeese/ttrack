cmake_minimum_required(VERSION 3.5)

project(ttrack LANGUAGES CXX)

set(HDR_FILES
  community.h
  communitydelegate.h
  communitymodel.h
  communityview.h
  mainwindow.h
  project.h
  reportmodel.h
  switch.h
  workperiod.h
)

set(SRC_FILES
  community.cpp
  communitydelegate.cpp
  communitymodel.cpp
  communityview.cpp
  mainwindow.cpp
  main.cpp
  project.cpp
  reportmodel.cpp
  switch.cpp
  workperiod.cpp
)

set(UI_FILES
  mainwindow.ui
)

add_executable(ttrack ${HDR_FILES} ${SRC_FILES} ${UI_FILES})

target_link_libraries(ttrack PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
