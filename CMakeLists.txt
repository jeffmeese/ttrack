cmake_minimum_required(VERSION 3.5)

project(ttrack LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

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
