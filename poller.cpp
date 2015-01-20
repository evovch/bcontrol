#include "poller.h"
#include <QFile>
#include <QTimer>
#include <QString>
#include <QDebug>

poller::poller()
{
    //trim non-simetric (bigger) part of range
    if(maxX-centerX > centerX-minX)maxX=centerX+(centerX-minX);
    else minX=centerX-(maxX-centerX);

    QTimer *pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(_onPollTimer()));
    pollTimer->start(100);
}

void poller::_onPollTimer(void) {
    int x = readAdcValue("0");
    x = 210;

    if(abs(x-lastX > adcNoiseThreshold)) {
        lastX = x;
        x = ((x - minX) - (maxX - minX)/2) * (double)((double)realRangeX/(maxX - minX));
        qDebug() << "got x:" << x;

        emit valueChangedX(x);
    }

 /    int y = readAdcValue(1);
//    int z = readAdcValue(2);
}

int poller::readAdcValue(QString sid) {
    QString fn = "/sys/bus/iio/devices/iio:device0/in_voltage"+ sid + "_raw";
    QFile inputFile(fn);
    QString line;
    if (inputFile.open(QIODevice::ReadOnly)) {
           line = inputFile.readLine();
    }
    else {
        qDebug() << "can't read ADC - device not found ("+ fn +"). Try 'echo BB-ADC > /sys/devices/bone_capemgr.*/slots'";
    }
    inputFile.close();

    return line.toInt();
}
