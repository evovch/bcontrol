#include "poller.h"
#include <QFile>
#include <QTimer>
#include <QString>
#include <QDebug>

poller::poller(uint mv)
{
    //trim non-simetric (bigger) part of range
    centerX = readAdcValue("6");
    rangeX = centerX * 2;
    centerY = readAdcValue("0");
    rangeY = centerY * 2;
    centerZ = readAdcValue("2");
    rangeZ = centerZ * 2;

    maxValue = mv;
    maxNormalizedValue = 100;

    QTimer *pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(_onPollTimer()));
    pollTimer->start(30);
}

int poller::normalizeValue(int val) {
    int res = val * (double)(maxNormalizedValue / maxValue);
    if((res > 0) && (res > maxNormalizedValue))res=maxNormalizedValue;
    else if ((res < 0) && (res < -1*maxNormalizedValue))res=-1*maxNormalizedValue;

    return res;
}

void poller::_onPollTimer(void) {
    int x = readAdcValue("6");
    if(abs(x-lastX) > adcNoiseThreshold) {
        lastX = x;
        x = normalizeValue((x - rangeX/2) * (double)((double)realRangeX/rangeX));
        qDebug() << "got x:" << x;
        emit valueChangedX(-1*x);
    }

    int y = readAdcValue("0");
    if(abs(y-lastY) > adcNoiseThreshold) {
        lastY = y;
        y = normalizeValue((y - rangeY/2) * (double)((double)realRangeY/rangeY));
        qDebug() << "got y:" << y;
        emit valueChangedY(-1*y);
    }

    int z = readAdcValue("2");
    if(abs(z-lastZ) > adcNoiseThreshold) {
        lastZ = z;
        z = normalizeValue((z - rangeZ/2) * (double)((double)realRangeZ/rangeZ));
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



