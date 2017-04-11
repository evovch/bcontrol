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

release: DESTDIR = ../qbone2-build-release
debug:   DESTDIR = ../qbone2-build-debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

CONFIG += c++11

#QMAKE_CXXFLAGS += -fpermissive -I/usr/include -I/opt/arm/include
#QMAKE_LFLAGS += -L/opt/arm/lib -L/opt/arm/lib -lturbojpeg

QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

TEMPLATE = app

LIBS += -lturbojpeg

INCLUDEPATH += ../

HEADERS += ../bsocket.h \
    ../controlgraph.h \
    ../bgraphicsellipseitem.h \
    ../focuspoint.h \
    ../btypes.h \
    ../liveviewsocket.h \
    ../fastpixmapitem.h \
    gpioint.h \
    poller.h \
    bjoycontrol.h \
    mainbox.h \
    eqepint.h

SOURCES += ../bsocket.cpp \
    ../controlgraph.cpp \
    ../bgraphicsellipseitem.cpp \
    ../focuspoint.cpp \
    ../liveviewsocket.cpp \
    ../fastpixmapitem.cpp \
    gpioint.cpp \
    bjoy.cpp \
    poller.cpp \
    bjoycontrol.cpp \
    mainbox.cpp \
    eqepint.cpp

FORMS += \
    mainbox.ui
