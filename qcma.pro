#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T15:34:17
#
#-------------------------------------------------

QT       += core \
            gui \
            widgets \
            network

TARGET = qcma

TEMPLATE = app

SOURCES += main.cpp \
    qcma.cpp \
    wirelessworker.cpp \
    listenerworker.cpp \
    capability.cpp \
    database.cpp \
    cmaobject.cpp \
    cmarootobject.cpp \
    utils.cpp \
    mainwidget.cpp \
    configwidget.cpp \
    singleapplication.cpp \
    baseworker.cpp \
    sforeader.cpp

HEADERS += \
    qcma.h \
    wirelessworker.h \
    listenerworker.h \
    capability.h \
    database.h \
    cmaobject.h \
    cmarootobject.h \
    utils.h \
    mainwidget.h \
    configwidget.h \
    singleapplication.h \
    baseworker.h \
    sforeader.h

CONFIG += link_pkgconfig
PKGCONFIG += libvitamtp libmediainfo

QMAKE_CXXFLAGS += -Wno-write-strings -Wall

RESOURCES += \
    qcmares.qrc

OTHER_FILES += \
    psp2-updatelist.xml

FORMS += \
    configwidget.ui