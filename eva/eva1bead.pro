#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T09:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eva1bead
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    start.cpp \
    game.cpp \
    resourcemanager.cpp

HEADERS  += mainwindow.h \
    start.h \
    game.h \
    resourcemanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    img/pictures.qrc
