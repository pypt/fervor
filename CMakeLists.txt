cmake_minimum_required(VERSION 2.8.3)
project(Fervor)
find_package(Qt4 REQUIRED)
set(QT_USE_QTNETWORK true)
set(QT_USE_QTWEBKIT true)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
if(DEFINED FORVERT_APP_VERSION)
  add_definitions(-DFV_APP_VERSION="${FORVERT_APP_VERSION")
else()
  add_definitions(-DFV_APP_VERSION="1.0")
  message(WARNING "No version information for Forvert given (please set FORVERT_APP_VERSION)! Assuming 1.0.")
endif()
if(DEFINED FORVERT_APP_NAME)
  add_definitions(-DFV_APP_NAME="${FORVERT_APP_NAME")
else()
  add_definitions(-DFV_APP_NAME="App Name")
  message(WARNING "No application name for Forvert given (please set FORVERT_APP_NAME)! Assuming 'App Name'.")
endif()

set(SOURCES
  fvavailableupdate.cpp
  fvignoredversions.cpp
  fvplatform.cpp
  fvupdateconfirmdialog.cpp
  fvupdater.cpp
  fvupdatewindow.cpp
  fvversioncomparator.cpp
)

set(MOC_HEADERS
  fvavailableupdate.h
  fvignoredversions.h
  fvplatform.h
  fvupdateconfirmdialog.h
  fvupdater.h
  fvupdatewindow.h
)

set(UIS
  fvupdateconfirmdialog.ui
  fvupdatewindow.ui
)

qt4_wrap_ui(UI_HEADERS ${UIS})
qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)
add_library(Fervor ${SOURCES} ${MOC_HEADERS} ${MOC_SOURCES} ${UIS})

if(FERVOR_BUILD_SAMPLE)
  add_subdirectory(sample)
endif()