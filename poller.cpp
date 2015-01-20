#include "poller.h"
#include <QFile>
#include <QTimer>
#include <QString>
#include <QDebug>

poller::poller()
{
    //trim non-simetric (bigger) part of range
    centerX = readAdcValue("0");
    rangeX = centerX * 2;
    centerY = readAdcValue("1");
    rangeY = centerY * 2;
    centerZ = readAdcValue("2");
    rangeZ = centerZ * 2;

    QTimer *pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(_onPollTimer()));
    pollTimer->start(100);
}

void poller::_onPollTimer(void) {
    int x = readAdcValue("0");
    if(abs(x-lastX) > adcNoiseThreshold) {
        lastX = x;
        x = (x - rangeX/2) * (double)((double)realRangeX/rangeX);
        qDebug() << "got x:" << x;
        emit valueChangedX(x);
    }

    int y = readAdcValue("1");
    if(abs(y-lastY) > adcNoiseThreshold) {
        lastY = y;
        y = (y - rangeY/2) * (double)((double)realRangeY/rangeY);
        qDebug() << "got y:" << y;
        emit valueChangedY(y);
    }

    int z = readAdcValue("2");
    if(abs(z-lastZ) > adcNoiseThreshold) {
        lastZ = z;
        z = (z - rangeZ/2) * (double)((double)realRangeZ/rangeZ);
        qDebug() << "got z:" << z;
        emit valueChangedZ(z);
    }

//    int y = readAdcValue(1);
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
