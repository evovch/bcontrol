QT += widgets
QT += network

CONFIG += c++11

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
    timelapse.cpp


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
    timelapse.h

FORMS += \
    main.ui \
    fhead.ui \
    tiltcontrolwidget.ui \
    pancontrolwidget.ui \
    slidercontrolwidget.ui \
    bmotion.ui \
    mainwindow.ui \
    camera.ui \
    timelapse.ui

