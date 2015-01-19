#include "poller.h"
#include <QFile>
#include <QTimer>

poller::poller()
{
    QTimer pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), socket, SLOT(_onPollTimer()));
    pollTimer->start(1000);
}

poller::_onPollTimer() {
    int x = readAdcValue(0);

    qDebug() << "got " << x << "\n";
//    int y = readAdcValue(1);
//    int z = readAdcValue(2);
}

int poller::readAdcValue(QString sid) {
    QFile inputFile("/sys/bus/iio/devices/iio:device0/in_voltage"+ sid + "_raw");
    QString line;
    if (inputFile.open(QIODevice::ReadOnly)) {
           line = in.readLine();
    }
    else {
        qDebug() << "can't read ADC - device not found. Try 'echo BB-ADC > /sys/devices/bone_capemgr.*/slots'";
    }
    inputFile.close();

    return QString::number(line);
}
