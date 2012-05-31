QT += core gui webkit

DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"

# FIXME unit tests
DEFINES += FV_DEBUG=1
DEPENDPATH += "$$PWD/tests/"
INCLUDEPATH += "$$PWD/tests/"
CONFIG += qtestlib



DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

SOURCES += fvupdatewindow.cpp \
	fvupdater.cpp \
	fvversioncomparator.cpp \
	tests/fvversioncomparatortest.cpp

HEADERS += fvupdatewindow.h \
	fvupdateconfig.h \
	fvupdater.h \
	fvversioncomparator.h \
	tests/fvversioncomparatortest.h

FORMS += fvupdatewindow.ui

TRANSLATIONS += fervor_lt.ts
CODECFORTR = UTF-8
