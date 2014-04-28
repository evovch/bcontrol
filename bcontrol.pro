QT += widgets
QT += network

CONFIG += c++11

SOURCES += \
    main.cpp \
    bsocket.cpp \
    bslider.cpp \
    blabel.cpp \
    fhead.cpp \
    tiltcontrolwidget.cpp \
    pancontrolwidget.cpp \
    slidercontrolwidget.cpp \
    basic.cpp \
    motorcontrolwidget.cpp \
    bclient.cpp \
    controlgraph.cpp


HEADERS += \
    bsocket.h \
    bslider.h \
    blabel.h \
    fhead.h \
    tiltcontrolwidget.h \
    slidercontrolwidget.h \
    pancontrolwidget.h \
    motorcontrolwidget.h \
    bclient.h \
    controlgraph.h

FORMS += \
    main.ui \
    fhead.ui \
    tiltcontrolwidget.ui \
    pancontrolwidget.ui \
    slidercontrolwidget.ui

