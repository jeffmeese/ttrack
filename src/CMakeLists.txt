cmake_minimum_required(VERSION 3.5)

project(ttrack LANGUAGES CXX)

set(HDR_FILES
  community.h
  mainwindow.h
  project.h
  projectmodel.h
  switch.h
  workperiod.h
)

set(SRC_FILES
  community.cpp
  mainwindow.cpp
  main.cpp
  project.cpp
  projectmodel.cpp
  switch.cpp
  workperiod.cpp
)

set(UI_FILES
  mainwindow.ui
)

add_executable(ttrack ${HDR_FILES} ${SRC_FILES} ${UI_FILES})

target_link_libraries(ttrack PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
