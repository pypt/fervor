# ------------------------------------------------
# Sample Fervor application
# ------------------------------------------------

#contains(QT_VERSION, ^5\\..[0-9]\\.*){
#    QT += core widgets
#}else{
#    QT += core gui
#}
QT += widgets webkitwidgets
TARGET = Sample
VERSION = 1.0
TEMPLATE = app
#DEFINES += QUAZIP_BUILD
#CONFIG(staticlib): DEFINES += QUAZIP_STATIC
#DEFINES +=QUAZIP_STATIC
DEFINES += NOMINMAX
mac:ICON = sample.icns
win32:RC_FILE = sample.rc

INCLUDEPATH += $$PWD




# Fervor autoupdater
# (set TARGET and VERSION of your app before including Fervor.pri)
!include("../Fervor.pri") {
	error("Unable to include Fervor autoupdater.")
}

# The sample application
SOURCES += main.cpp \
		mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui
