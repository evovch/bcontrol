#include <QtCore/QCoreApplication>
#include <QDebug>
#include "bsocket.h"
#include "poller.h"
#include "bjoycontrol.h"
#include "gpioint.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
//    bSocket *socket = new bSocket();
//    socket->reconnect();

    qDebug() << "strarting up bJoy";

    poller *p = new poller();
    bJoyControl *bjc = new bJoyControl();

    gpioInt *buttonsGpio = new gpioInt(66);
    buttonsGpio->start();

    QObject::connect(p, SIGNAL(valueChangedX(int)), bjc, SLOT(_onSpeedChangedX(int)));
    QObject::connect(p, SIGNAL(valueChangedY(int)), bjc, SLOT(_onSpeedChangedY(int)));
    QObject::connect(p, SIGNAL(valueChangedZ(int)), bjc, SLOT(_onSpeedChangedZ(int)));

    buttonsGpio->exit();

    return a.exec();
}
