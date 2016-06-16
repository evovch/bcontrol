#include "poller.h"
#include <QFile>
#include <QTimer>
#include <QString>
#include <QDebug>

poller::poller()
{
    //trim non-simetric (bigger) part of range
    centerX = readAdcValue("6");
    rangeX = centerX * 2;
    centerY = readAdcValue("0");
    rangeY = centerY * 2;
    centerZ = readAdcValue("2");
    rangeZ = centerZ * 2;

    maxNormalizedValue = 100;

    QTimer *pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(_onPollTimer()));
    pollTimer->start(30);
}

void poller::_onPollTimer(void) {
    int x = readAdcValue("6");
    if(abs(x-lastX) > adcNoiseThreshold) {
        lastX = x;
        x = x - rangeX/2;
        x = x * ((double)maxNormalizedValue/(rangeX/2));
        if(x > -3 && x < 3)x=0;
        qDebug() << "got x:" << x;
        emit valueChangedX(-1*x);
    }

    int y = readAdcValue("0");
    if(abs(y-lastY) > adcNoiseThreshold) {
        lastY = y;
        y = y - rangeY/2;
        y = y * ((double)maxNormalizedValue/(rangeY/2));
        if(y > -3 && y < 3)y=0;
        qDebug() << "got y:" << y;
        emit valueChangedY(-1*y);
    }

    int z = readAdcValue("2");
    if(abs(z-lastZ) > adcNoiseThreshold) {
        lastZ = z;
        z = z - rangeZ/2;
        z = z * ((double)maxNormalizedValue/(rangeZ/2));
        if(z > -3 && z < 3)z=0;
        qDebug() << "got z:" << z;
        emit valueChangedZ(z);
    }
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



