#-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T21:05:19
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = bjoy 
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -fpermissive

TEMPLATE = app

HEADERS += bsocket.h \
    poller.h \
    bjoycontrol.h \
    gpioint.h

SOURCES += bjoy.cpp \
    bjoycontrol.cpp \
    gpioint.cpp \
    bsocket.cpp \
    poller.cpp
