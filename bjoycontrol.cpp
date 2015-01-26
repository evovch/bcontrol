#include "bjoycontrol.h"
#include <QDebug>

bJoyControl::bJoyControl(QObject *parent) :
    QObject(parent)
{
    bSocket *socket = new bSocket();
    socket->reconnect();
}

void bJoyControl::_onSpeedChangedX(int val) {
    socket->send("motor_pan", "set_speed", val * 5);
    qDebug() << "new Pan speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedY(int val) {
    socket->send("motor_tilt", "set_speed", val * 5);
    qDebug() << "new Tilt speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedZ(int val) {
    socket->send("motor_ziim", "set_speed", val * 5);
    qDebug() << "new Zoom speed by bJoy: " << val;
}
