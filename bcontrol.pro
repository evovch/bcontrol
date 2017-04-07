QT += widgets
QT += network

CONFIG += c++11

#QMAKE_CXXFLAGS += -fpermissive -I/usr/include -I/opt/libjpeg-turbo/include
#QMAKE_LFLAGS += -L/opt/libjpeg-turbo/lib -lturbojpeg

#QMAKE_MAC_SDK = macosx10.11

SOURCES += \
    main.cpp \
    bsocket.cpp \
    bslider.cpp \
    blabel.cpp \
    bcontrolwidget.cpp \
    tiltcontrolwidget.cpp \
    pancontrolwidget.cpp \
    slidercontrolwidget.cpp \
    zoomcontrolwidget.cpp \
    focuscontrolwidget.cpp \
    basic.cpp \
    motorcontrolwidget.cpp \
    bclient.cpp \
    controlgraph.cpp \
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
    motorwidget.cpp \
    network.cpp \
    fastpixmapitem.cpp

HEADERS += \
    bsocket.h \
    bslider.h \
    blabel.h \
    bcontrolwidget.h \
    tiltcontrolwidget.h \
    pancontrolwidget.h \
    slidercontrolwidget.h \
    zoomcontrolwidget.h \
    focuscontrolwidget.h \
    motorcontrolwidget.h \
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
    camera.h \
    focuspoint.h \
    timelapse.h \
    motorwidget.h \
    network.h \
    fastpixmapitem.h

FORMS += \
    main.ui \
    fhead.ui \
    tiltcontrolwidget.ui \
    pancontrolwidget.ui \
    slidercontrolwidget.ui \
    zoomcontrolwidget.ui \
    focuscontrolwidget.ui \
    bmotion.ui \
    mainwindow.ui \
    camera.ui \
    timelapse.ui \
    limitswindow.ui \
    motorwidget.ui \
    network.ui
