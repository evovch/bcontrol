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

release: DESTDIR = ../bjoy-build-release
debug:   DESTDIR = ../bjoy-build-debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

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
    fastpixmapitem.h \
    eqepint.h

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
    fastpixmapitem.cpp \
    eqepint.cpp

FORMS += \
    mainbox.ui
