#include "bclient.h"
#include <QDebug>

bClient::bClient(bSocket *socket, Ui_fhead *ui, QObject *parent) :
    QObject(parent)
{
    this->socket = socket;
    this->ui = ui;

    ui->caprureButton->setFocus();

    cg = new controlGraph(ui->headGraph);

    QObject::connect(ui->panControl, SIGNAL(speedChanged(int)), this, SLOT(_onPanSpeedChanged(int)));
    QObject::connect(ui->panControl, SIGNAL(positionChanged(int)), this, SLOT(_onPanPositionChanged(int)));

    QObject::connect(cg, SIGNAL(panPositionRequested(int)), this, SLOT(_onPanPositionChanged(int)));
//    QObject::connect(cg, SIGNAL(tiltPositionRequested(int)), this, SLOT(_onTiltPositionChanged(int)));

    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString)), this, SLOT(_onDataReceived(QString,QString,QString)));
}

void bClient::_onPanSpeedChanged(int value) {
    socket->send("motor_pan", "set_speed", QString::number(value));
}

void bClient::_onPanPositionChanged(int value) {
    socket->send("motor_pan", "set_position", QString::number(value));
}

void bClient::_onDataReceived(QString dev, QString key, QString value) {
    if(dev=="motor_pan" && key=="status_position") {
        ui->panControl->setPosition(value.toInt());
        cg->setPanPosition(value.toInt());
    }
}
