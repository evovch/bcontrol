#include "bjoycontrol.h"
#include "mainBox.h"
#include <QDebug>

bJoyControl::bJoyControl(QObject *parent) :
    QObject(parent)
{
    mainBox *mb = new mainBox();
    mb->show();

    cg = new controlGraph(mb);

    socketLv = new liveViewSocket();
    socketLv->reconnect();

    QObject::connect(socketLv, SIGNAL(gotAFrame(QByteArray)), cg, SLOT(_onGotAFrame(QByteArray)));

    socket = new bSocket();
    socket->reconnect();
}

void bJoyControl::_onSpeedChangedX(int val) {
    socket->send("motor_pan", "set_speed", QString::number(val * 5));
    qDebug() << "new Pan speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedY(int val) {
    socket->send("motor_tilt", "set_speed", QString::number(val * 5));
    qDebug() << "new Tilt speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedZ(int val) {
    socket->send("motor_ziim", "set_speed", QString::number(val * 5));
    qDebug() << "new Zoom speed by bJoy: " << val;
}

void bJoyControl::_onAfOn() {
    socket->send("cam", "af_trigger", "1");
    qDebug() << "sending AF on";
}

void bJoyControl::_onAfOff() {
    socket->send("cam", "af_trigger", "0");
    qDebug() << "sending AF off";
}
