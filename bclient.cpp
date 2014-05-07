#include "bclient.h"
#include <QDebug>

bClient::bClient(bSocket *socket, Ui_fhead *ui, QObject *parent) :
    QObject(parent)
{
    this->socket = socket;
    this->ui = ui;

    ui->caprureButton->setFocus();

    cg = new controlGraph(ui->headGraph);
    cg->setFixedPoints(&fixedPoints);


    QObject::connect(ui->panControl, SIGNAL(speedChanged(int)), this, SLOT(_onPanSpeedChanged(int)));
    QObject::connect(ui->panControl, SIGNAL(positionChanged(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(cg, SIGNAL(panPositionRequested(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(this, SIGNAL(fixedPointsUpdated()), cg, SLOT(_onFixedPointsUpdated()));
//    QObject::connect(cg, SIGNAL(tiltPositionRequested(int)), this, SLOT(_onTiltPositionChanged(int)));
    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString,QStringList)), this, SLOT(_onDataReceived(QString,QString,QString,QStringList)));

}

void bClient::addFixedPoint(QString id, controlGraph::fixedPoint fp) {
    fixedPoints.insert(id, fp);

    emit fixedPointsUpdated();
}

void bClient::removeFixedPoint(QString id) {
    if(fixedPoints.find(id)==fixedPoints.end())return;

    fixedPoints.remove(id);

    emit fixedPointsUpdated();
}

void bClient::_onPanSpeedChanged(int value) {
    socket->send("motor_pan", "set_speed", QString::number(value));
}

void bClient::_onPanPositionChanged(int value) {
    socket->send("motor_pan", "set_position", QString::number(value));
}

void bClient::_onDataReceived(QString dev, QString key, QString value, QStringList params) {
    if(dev=="motor_pan" && key=="status_position") {
        ui->panControl->setPosition(value.toInt());
        cg->setPanPosition(value.toInt());
    }

    if(dev=="fixed_point" && key=="get") {
        removeFixedPoint(value);

        controlGraph::fixedPoint p;
        p.name = params[0];
        p.panValue = params[1].toInt();
        p.tiltValue = params[2].toInt();

        addFixedPoint(value, p);

    }
}
