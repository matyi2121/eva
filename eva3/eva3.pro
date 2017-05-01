#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T09:29:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eva3
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp\
        awari.cpp \
    startview.cpp \
    gameview.cpp \
    gamemodel.cpp

HEADERS  += awari.h \
    startview.h \
    gameview.h \
    gamemodel.h

FORMS    +=
