QT += core gui webkit network

DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"



# FIXME unit tests
#DEFINES += FV_DEBUG=1
#DEPENDPATH += "$$PWD/tests/"
#INCLUDEPATH += "$$PWD/tests/"
#CONFIG += qtestlib
#SOURCES += tests/fvversioncomparatortest.cpp
#HEADERS += tests/fvversioncomparatortest.h



DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

SOURCES += fvupdatewindow.cpp \
	fvupdater.cpp \
	fvversioncomparator.cpp \
	fvplatform.cpp \
	fvignoredversions.cpp \
	fvavailableupdate.cpp \
	fvupdateconfirmdialog.cpp

HEADERS += fvupdatewindow.h \
	fvupdater.h \
	fvversioncomparator.h \
	fvplatform.h \
	fvignoredversions.h \
	fvavailableupdate.h \
	fvupdateconfirmdialog.h

FORMS += fvupdatewindow.ui \
	fvupdateconfirmdialog.ui

TRANSLATIONS += fervor_lt.ts
CODECFORTR = UTF-8
