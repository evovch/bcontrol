#-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T21:05:19
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = bjoy 
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -fpermissive -I/usr/include
QMAKE_LFLAGS += -L/opt/libjpeg-turbo-arm/lib -lturbojpeg

TEMPLATE = app

HEADERS += bsocket.h \
    poller.h \
    bjoycontrol.h \
    gpioint.h \
    controlgraph.h \
    bgraphicsellipseitem.h \
    mainbox.h \
    focuspoint.h \
    btypes.h \
    liveviewsocket.h

SOURCES += bjoy.cpp \
    bjoycontrol.cpp \
    gpioint.cpp \
    bsocket.cpp \
    poller.cpp \
    controlgraph.cpp \
    bgraphicsellipseitem.cpp \
    mainbox.cpp \
    focuspoint.cpp \
    liveviewsocket.cpp

FORMS += \
    mainbox.ui
