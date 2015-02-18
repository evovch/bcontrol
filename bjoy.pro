#-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T21:05:19
#
#-------------------------------------------------

#QT       += core
#QT       += gui
QT       += network
QT       += widgets

TARGET = bjoy 
CONFIG   += console
#CONFIG   -= app_bundle

CONFIG += c++11

QMAKE_CXXFLAGS += -fpermissive -I/usr/include -I/opt/libjpeg-turbo/include
QMAKE_LFLAGS += -L/opt/libjpeg-turbo-arm/lib -L/opt/libjpeg-turbo/lib -lturbojpeg

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
    liveviewsocket.h \
    fastpixmapitem.h

SOURCES += bjoy.cpp \
    bjoycontrol.cpp \
    gpioint.cpp \
    bsocket.cpp \
    poller.cpp \
    controlgraph.cpp \
    bgraphicsellipseitem.cpp \
    mainbox.cpp \
    focuspoint.cpp \
    liveviewsocket.cpp \
    fastpixmapitem.cpp

FORMS += \
    mainbox.ui
