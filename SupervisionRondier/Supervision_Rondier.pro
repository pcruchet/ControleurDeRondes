#-------------------------------------------------
#
# Project created by QtCreator 2017-05-18T22:35:02
#
#-------------------------------------------------

QT       += core gui sql xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Supervision_Rondier
TEMPLATE = app


SOURCES += main.cpp\
        supervisionrondier.cpp \
    accesmysql.cpp \
    agent.cpp \
    ihmagent.cpp \
    ihmidentification.cpp \
    ihmpointeau.cpp \
    ihmronde.cpp \
    message.cpp \
    pointeau.cpp \
    ronde.cpp \
    tempspointage.cpp \
    accesxml.cpp \
    parametre.cpp \
    scanner.cpp \
    communicationadb.cpp \
    gestionsqlite.cpp \
    ihmsynchronisation.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    qdevicewatcher_win32.cpp \
    associationagentsrondes.cpp \
    gestionsmartphones.cpp \
    ihmassociation.cpp \
    ihmrapport.cpp \
    rapport.cpp

HEADERS  += supervisionrondier.h \
    accesmysql.h \
    agent.h \
    ihmagent.h \
    ihmidentification.h \
    ihmpointeau.h \
    ihmronde.h \
    message.h \
    pointeau.h \
    ronde.h \
    tempspointage.h \
    accesxml.h \
    parametre.h \
    scanner.h \
    communicationadb.h \
    gestionsqlite.h \
    ihmsynchronisation.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    associationagentsrondes.h \
    gestionsmartphones.h \
    ihmassociation.h \
    ihmrapport.h \
    rapport.h

FORMS    += supervisionrondier.ui

RESOURCES += \
    ressource.qrc

RC_FILE = application.rc

DISTFILES += \
    libQDeviceWatcher.pri
