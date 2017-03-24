#-------------------------------------------------
#
# Project created by QtCreator 2017-03-11T10:48:15
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eva2
TEMPLATE = app


SOURCES += main.cpp \
    tron.cpp \
    gameview.cpp \
    gamemodel.cpp \
    startview.cpp \
    startmodel.cpp \
    resourcemanager.cpp \
    player.cpp

HEADERS  += \
    tron.h \
    gameview.h \
    gamemodel.h \
    startview.h \
    startmodel.h \
    resourcemanager.h \
    player.h

RESOURCES += \
    img/pictures.qrc

DISTFILES +=
