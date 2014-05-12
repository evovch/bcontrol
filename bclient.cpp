#include "bclient.h"
#include <QDebug>

bClient::bClient(bSocket *socket, Ui_fhead *ui, QObject *parent) :
    QObject(parent)
{
    this->socket = socket;
    this->ui = ui;

    ui->caprureButton->setFocus();

    fixedPoints = fixedPointHash();
    cg = new controlGraph(ui->headGraph);
    cg->setFixedPoints(&fixedPoints);

    fpModel = new bFixedPointModel(0, &fixedPoints);
    ui->fpTableView->setModel( fpModel );


    currentFixedPointId = "p1";
    fpModel->selectFixedPoint(currentFixedPointId);

    QObject::connect(ui->fpTableView, SIGNAL(clicked(QModelIndex)), fpModel, SLOT(_onCellClicked(QModelIndex)));

    QObject::connect(fpModel, SIGNAL(removeFixedPointClicked(QString)), this, SLOT(_onRemoveFixedPoint(QString)));
    QObject::connect(fpModel, SIGNAL(selectFixedPointClicked(QString)), this, SLOT(_onSelectFixedPoint(QString)));
    QObject::connect(fpModel, SIGNAL(selectRow(int)), ui->fpTableView, SLOT(selectRow(int)));

    ui->fpTableView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->fpTableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->fpTableView->horizontalHeader()->setResizeMode(2, QHeaderView::Fixed);
    ui->fpTableView->horizontalHeader()->resizeSection(2, 25);

    QObject::connect(ui->panControl, SIGNAL(speedChanged(int)), this, SLOT(_onPanSpeedChanged(int)));
    QObject::connect(ui->panControl, SIGNAL(positionChanged(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(ui->tiltControl, SIGNAL(speedChanged(int)), this, SLOT(_onTiltSpeedChanged(int)));
    QObject::connect(ui->tiltControl, SIGNAL(positionChanged(int)), this, SLOT(_onTiltPositionChanged(int)));

    QObject::connect(ui->fixedPointButton, SIGNAL(pressed()), this, SLOT(_onfixedPointButtonPressed()));

    QObject::connect(cg, SIGNAL(panPositionRequested(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(cg, SIGNAL(tiltPositionRequested(int)), this, SLOT(_onTiltPositionChanged(int)));

    QObject::connect(this, SIGNAL(fixedPointsUpdated()), cg, SLOT(_onFixedPointsUpdated()));
    QObject::connect(this, SIGNAL(fixedPointsUpdated()), fpModel, SLOT(_onFixedPointsUpdated()));
    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString,QStringList)), this, SLOT(_onDataReceived(QString,QString,QString,QStringList)));

}

void bClient::_onfixedPointButtonPressed(void) {
    qDebug() << "fixPoint pressed!";

    fixedPoint fp;

    sendFixedPoint(0, fp);
}

void bClient::sendFixedPoint(QString id, fixedPoint fp) {
    QStringList params;
    params.append(fp.name);

    socket->send("fixed_point", "set_current", id,  params);
}

void bClient::addFixedPoint(QString id, fixedPoint fp) {
    fixedPoints.insert(id, fp);
}

void bClient::removeFixedPoint(QString id) {
    if(fixedPoints.find(id)==fixedPoints.end())return;

    fixedPoints.remove(id);
}

void bClient::clearFixedPoints(void) {
//    qDebug() << "clearing fps";
    fixedPoints.clear();
}

void bClient::refreshFixedPoints(void) {
//    qDebug() << "resreshing fps";

    emit fixedPointsUpdated();
}


void bClient::_onPanSpeedChanged(int value) {
    socket->send("motor_pan", "set_speed", QString::number(value));
}

void bClient::_onPanPositionChanged(int value) {
    socket->send("motor_pan", "set_position", QString::number(value));
}

void bClient::_onTiltSpeedChanged(int value) {
    socket->send("motor_tilt", "set_speed", QString::number(value));
}

void bClient::_onTiltPositionChanged(int value) {
    socket->send("motor_tilt", "set_position", QString::number(value));
}

void bClient::_onRemoveFixedPoint(QString id) {
    socket->send("fixed_point", "remove", id);
}

void bClient::_onSelectFixedPoint(QString id) {
     socket->send("fixed_point", "select", id);
}

void bClient::_onDataReceived(QString dev, QString key, QString value, QStringList params) {
    if(dev=="motor_pan" && key=="status_position") {
        ui->panControl->setPosition(value.toInt());
        cg->setPanPosition(value.toInt());
    }
    if(dev=="motor_tilt" && key=="status_position") {
        ui->tiltControl->setPosition(value.toInt());
        cg->setTiltPosition(value.toInt());
    }

    if(dev=="fixed_point" && key=="get") {
        removeFixedPoint(value);

        fixedPoint p;
        p.name = params[0];
        p.panValue = params[1].toInt();
        p.tiltValue = params[2].toInt();

        addFixedPoint(value, p);

    }

    if(dev=="fixed_point" && key=="clear") {
        clearFixedPoints();
    }

    if(dev=="fixed_point" && key=="refresh") {
        refreshFixedPoints();
    }

    if(dev=="fixed_point" && key=="select") {
        currentFixedPointId = value;
        fpModel->selectFixedPoint(currentFixedPointId);
    }
}
