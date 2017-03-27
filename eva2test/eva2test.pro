#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T13:46:54
#
#-------------------------------------------------

QT       += widgets testlib
QMAKE_CXXFLAGS += -std=c++11
TARGET = gamemodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += gamemodeltest.cpp \
    gamemodel.cpp \
    player.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    gamemodel.h \
    player.h
