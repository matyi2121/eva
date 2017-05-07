#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T15:09:01
#
#-------------------------------------------------

QT       += testlib

QT       -= gui
QMAKE_CXXFLAGS += -std=c++11
TARGET = tst_eva3_unittest_mock
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_eva3_unittest_mock.cpp \
    gamemodel.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    gamemodel.h \
    resourcemanager.h \
    resourcemanager_mock.h
