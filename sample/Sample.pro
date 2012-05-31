# ------------------------------------------------
# Sample Fervor application
# ------------------------------------------------

QT       += core gui webkit

TARGET = Sample
VERSION = 1.0
TEMPLATE = app

!include("../Fervor.pri") {
	error("Unable to include Fervor autoupdater.")
}


SOURCES += main.cpp\
		mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
