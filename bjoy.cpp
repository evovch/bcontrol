#include <QtGui>
#include <QtCore>
#include <QApplication>
#include <QDebug>
#include "bsocket.h"
#include "poller.h"
#include "bjoycontrol.h"
#include "gpioint.h"
#include "eqepint.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
//    bSocket *socket = new bSocket();
//    socket->reconnect();

    qDebug() << "strarting up bJoy";

    poller *p = new poller(13);
    bJoyControl *bjc = new bJoyControl();

    unsigned int gpioArray[27] = {69,68,23,26,27,65,22,61,30,60,31,50,48,51,5,4,3,2,49,15,14,116,117,46,47};

    for(int i=0; i < 27; i++) {
        gpioInt *buttonGpio = new gpioInt(gpioArray[i]);
        buttonGpio->start();

        QObject::connect(buttonGpio, SIGNAL(gpioEdge(unsigned int, bool)), bjc, SLOT(_onGpioEdge(unsigned int, bool)));
    }

    eqepInt *topEqep = new eqepInt(0);
    topEqep->start();
    eqepInt *bottomsEqep = new eqepInt(2);
    bottomsEqep->start();

    QObject::connect(p, SIGNAL(valueChangedX(int)), bjc, SLOT(_onSpeedChangedX(int)));
    QObject::connect(p, SIGNAL(valueChangedY(int)), bjc, SLOT(_onSpeedChangedY(int)));
    QObject::connect(p, SIGNAL(valueChangedZ(int)), bjc, SLOT(_onSpeedChangedZ(int)));

//    afGpio->terminate();

    return a.exec();
}
