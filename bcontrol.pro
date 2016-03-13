QT += widgets
QT += network

CONFIG += c++11

QMAKE_CXXFLAGS += -fpermissive -I/usr/include -I/opt/libjpeg-turbo/include
QMAKE_LFLAGS += -L/opt/libjpeg-turbo/lib -lturbojpeg

QMAKE_MAC_SDK = macosx10.11

SOURCES += \
    main.cpp \
    bsocket.cpp \
    bslider.cpp \
    blabel.cpp \
    tiltcontrolwidget.cpp \
    pancontrolwidget.cpp \
    slidercontrolwidget.cpp \
    basic.cpp \
    motorcontrolwidget.cpp \
    bclient.cpp \
    controlgraph.cpp \
    bcontrolwidget.cpp \
    fhead.cpp \
    bgraphicsellipseitem.cpp \
    bfixedpointmodel.cpp \
    liveviewsocket.cpp \
    bcamparammodel.cpp \
    bmotion.cpp \
    mainwindow.cpp \
    camera.cpp \
    focuspoint.cpp \
    timelapse.cpp \
    zoomcontrolwidget.cpp \
    focuscontrolwidget.cpp \
    motorwidget.cpp \
    network.cpp \
    fastpixmapitem.cpp


HEADERS += \
    bsocket.h \
    bslider.h \
    blabel.h \
    tiltcontrolwidget.h \
    slidercontrolwidget.h \
    pancontrolwidget.h \
    motorcontrolwidget.h \
    bclient.h \
    controlgraph.h \
    bcontrolwidget.h \
    fhead.h \
    btypes.h \
    bgraphicsellipseitem.h \
    bfixedpointmodel.h \
    liveviewsocket.h \
    bcamparammodel.h \
    bmotion.h \
    mainwindow.h \
    camera.h \
    focuspoint.h \
    timelapse.h \
    zoomcontrolwidget.h \
    focuscontrolwidget.h \
    motorwidget.h \
    network.h \
    fastpixmapitem.h

FORMS += \
    main.ui \
    fhead.ui \
    tiltcontrolwidget.ui \
    pancontrolwidget.ui \
    slidercontrolwidget.ui \
    bmotion.ui \
    mainwindow.ui \
    camera.ui \
    timelapse.ui \
    zoomcontrolwidget.ui \
    focuscontrolwidget.ui \
    limitswindow.ui \
    motorwidget.ui \
    network.ui

