#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T14:08:44
#
#-------------------------------------------------

QT       += core gui widgets testlib
QMAKE_CXXFLAGS += -std=c++11
TARGET = gameviewtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += gameviewtest.cpp \
    gameview.cpp \
    resourcemanager.cpp \
    startview.cpp \
    tron.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    gameview.h \
    resourcemanager.h \
    startview.h \
    tron.h

RESOURCES += \
    pictures.qrc

DISTFILES +=
