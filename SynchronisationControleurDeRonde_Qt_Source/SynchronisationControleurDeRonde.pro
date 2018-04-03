#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T17:33:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SynchronisationControleurDeRonde
TEMPLATE = app


SOURCES += main.cpp\
        synchronisation.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    qdevicewatcher_win32.cpp \
    gestionqlite.cpp \
    communicationadb.cpp

HEADERS  += synchronisation.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    gestionsqlite.h \
    communicationadb.h

FORMS    += synchronisation.ui
