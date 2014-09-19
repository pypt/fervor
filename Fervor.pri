QT += core network
!build_pass:message("If you want to enable GUI for Fervor, add CONFIG += fervor_gui to your .pro file")
contains(QT_VERSION, ^5\\.[0-9]\\..*){
    fervor_gui {
        DEFINES += FV_GUI
        QT += webkitwidgets
    }
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/include/QtZlib
}else{
    fervor_gui {
        DEFINES += FV_GUI
        QT += gui webkit
    }
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/../../../../QtSources/4.8.1/src/3rdparty/zlib
}
DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"

PREVIOUS_FERVOR_GUI = $$cat($$PWD/fervor.gui)
fervor_gui {
    CURRENT_FERVOR_GUI = enabled
} else {
    CURRENT_FERVOR_GUI = disabled
}
# if last build was with another GUI option, recompile some files
!equals(PREVIOUS_FERVOR_GUI, $$CURRENT_FERVOR_GUI) {
    write_file($$PWD/fervor.gui, CURRENT_FERVOR_GUI)
    touch($$PWD/fvupdater.h, $$PWD/fervor.gui)
}

DEFINES += QUAZIP_BUILD QUAZIP_STATIC

INCLUDEPATH += $$PWD/quazip
HEADERS += $$PWD/quazip/crypt.h \
           $$PWD/quazip/ioapi.h \
           $$PWD/quazip/JlCompress.h \
           $$PWD/quazip/quaadler32.h \
           $$PWD/quazip/quachecksum32.h \
           $$PWD/quazip/quacrc32.h \
           $$PWD/quazip/quazip.h \
           $$PWD/quazip/quazipfile.h \
           $$PWD/quazip/quazipfileinfo.h \
           $$PWD/quazip/quazipnewinfo.h \
           $$PWD/quazip/unzip.h \
           $$PWD/quazip/zip.h
SOURCES += $$PWD/quazip/qioapi.cpp \
           $$PWD/quazip/JlCompress.cpp \
           $$PWD/quazip/quaadler32.cpp \
           $$PWD/quazip/quacrc32.cpp \
           $$PWD/quazip/quazip.cpp \
           $$PWD/quazip/quazipfile.cpp \
           $$PWD/quazip/quazipfileinfo.cpp \
           $$PWD/quazip/quazipnewinfo.cpp \
           $$PWD/quazip/unzip.c \
           $$PWD/quazip/zip.c

DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"
SOURCES += $$PWD/fvupdater.cpp \
        $$PWD/fvversioncomparator.cpp \
        $$PWD/fvplatform.cpp \
        $$PWD/fvignoredversions.cpp \
        $$PWD/fvavailableupdate.cpp

HEADERS += $$PWD/fvupdater.h \
        $$PWD/fvversioncomparator.h \
        $$PWD/fvplatform.h \
        $$PWD/fvignoredversions.h \
        $$PWD/fvavailableupdate.h

fervor_gui {
    SOURCES += $$PWD/fvupdatewindow.cpp \
            $$PWD/fvupdatedownloadprogress.cpp

    HEADERS += $$PWD/fvupdatewindow.h \
            $$PWD/fvupdatedownloadprogress.h

    FORMS += $$PWD/fvupdatewindow.ui \
            $$PWD/fvupdatedownloadprogress.ui
}


TRANSLATIONS += fervor_lt.ts
CODECFORTR = UTF-8
