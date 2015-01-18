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

HEADERS += bsocket.h

SOURCES += bjoy.cpp
SOURCES += bsocket.cpp
