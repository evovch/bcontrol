QT += widgets
QT += network

CONFIG += c++11
CONFIG += console

release: DESTDIR = ../qbone2-build-release
debug:   DESTDIR = ../qbone2-build-debug

QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

#QMAKE_CXXFLAGS += -fpermissive -I/usr/include -I/opt/libjpeg-turbo/include
#QMAKE_LFLAGS += -L/opt/libjpeg-turbo/lib -lturbojpeg

#QMAKE_MAC_SDK = macosx10.11

#LIBS += -L/home/evovch/Documents/DKV/libjpeg-turbo_build/
LIBS += -lturbojpeg

INCLUDEPATH += gui/

SOURCES += \
    main.cpp \
    bsocket.cpp \
    gui/bslider.cpp \
    gui/blabel.cpp \
    gui/bcontrolwidget.cpp \
    gui/tiltcontrolwidget.cpp \
    gui/pancontrolwidget.cpp \
    gui/slidercontrolwidget.cpp \
    gui/zoomcontrolwidget.cpp \
    gui/focuscontrolwidget.cpp \
    motorwidget.cpp \
    gui/motorcontrolwidget.cpp \
    basic.cpp \
    bclient.cpp \
    controlgraph.cpp \
    fhead.cpp \
    bgraphicsellipseitem.cpp \
    bfixedpointmodel.cpp \
    liveviewsocket.cpp \
    bcamparammodel.cpp \
    bmotion.cpp \
    mainwindow.cpp \
    gui/camera.cpp \
    focuspoint.cpp \
    timelapse.cpp \
    network.cpp \
    fastpixmapitem.cpp

HEADERS += \
    bsocket.h \
    gui/bslider.h \
    gui/blabel.h \
    gui/bcontrolwidget.h \
    gui/tiltcontrolwidget.h \
    gui/pancontrolwidget.h \
    gui/slidercontrolwidget.h \
    gui/zoomcontrolwidget.h \
    gui/focuscontrolwidget.h \
    motorwidget.h \
    gui/motorcontrolwidget.h \
    bclient.h \
    controlgraph.h \
    fhead.h \
    btypes.h \
    bgraphicsellipseitem.h \
    bfixedpointmodel.h \
    liveviewsocket.h \
    bcamparammodel.h \
    bmotion.h \
    mainwindow.h \
    gui/camera.h \
    focuspoint.h \
    timelapse.h \
    network.h \
    fastpixmapitem.h

FORMS += \
    main.ui \
    fhead.ui \
    gui/tiltcontrolwidget.ui \
    gui/pancontrolwidget.ui \
    gui/slidercontrolwidget.ui \
    gui/zoomcontrolwidget.ui \
    gui/focuscontrolwidget.ui \
    motorwidget.ui \
    bmotion.ui \
    mainwindow.ui \
    gui/camera.ui \
    timelapse.ui \
    limitswindow.ui \
    network.ui
