#-------------------------------------------------
#
# Project created by QtCreator 2012-04-18T13:27:45
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = Fervor
VERSION = 1.0
TEMPLATE = app

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += main.cpp\
        mainwindow.cpp \
    fvupdatewindow.cpp

HEADERS  += mainwindow.h \
    fvupdatewindow.h \
    fvupdateconfig.h

FORMS    += mainwindow.ui \
    fvupdatewindow.ui
