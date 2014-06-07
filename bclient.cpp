#include "bclient.h"
#include <QDebug>

bClient::bClient(Ui_fhead *ui, QObject *parent) :
    QObject(parent)
{
    socket = new bSocket();
    socket->reconnect();

    socketLv = new liveViewSocket();
    socketLv->reconnect();

    this->ui = ui;

    ui->captureButton->setFocus();

    fixedPoints = fixedPointHash();
    cg = new controlGraph(ui->headGraph);
    cg->setFixedPoints(&fixedPoints);

    fpModel = new bFixedPointModel(0, &fixedPoints);
    ui->fpTableView->setModel( fpModel );


//    currentFixedPointId = "p1";
//    fpModel->selectFixedPoint(currentFixedPointId);

    QObject::connect(socketLv, SIGNAL(gotAFrame(QByteArray)), cg, SLOT(_onGotAFrame(QByteArray)));

    QObject::connect(ui->fpTableView, SIGNAL(pressed(QModelIndex)), fpModel, SLOT(_onCellClicked(QModelIndex)));

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

    QObject::connect(ui->fixedPointButton, SIGNAL(pressed()), this, SLOT(_onFixedPointButtonPressed()));

    QObject::connect(ui->liveViewZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(_onLiveZoomSliderValueChanged(int)));

    QObject::connect(ui->liveViewButton, SIGNAL(pressed()), this, SLOT(_onLiveViewButtonPressed()));
    QObject::connect(ui->focusUpButton, SIGNAL(pressed()), this, SLOT(_onFocusUpButtonPressed()));
    QObject::connect(ui->focusDownButton, SIGNAL(pressed()), this, SLOT(_onFocusDownButtonPressed()));

    QObject::connect(ui->captureButton, SIGNAL(pressed()), this, SLOT(_onCaptureButtonPressed()));

    QObject::connect(ui->tlRunButton, SIGNAL(pressed()), this, SLOT(_onTlRunButtonPressed()));

    QObject::connect(cg, SIGNAL(panPositionRequested(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(cg, SIGNAL(tiltPositionRequested(int)), this, SLOT(_onTiltPositionChanged(int)));

    QObject::connect(this, SIGNAL(fixedPointsUpdated()), cg, SLOT(_onFixedPointsUpdated()));
    QObject::connect(this, SIGNAL(fixedPointsUpdated()), fpModel, SLOT(_onFixedPointsUpdated()));
    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString,QStringList)), this, SLOT(_onDataReceived(QString,QString,QString,QStringList)));

}

void bClient::_onFixedPointButtonPressed(void) {
    qDebug() << "fixPoint pressed!";

    fixedPoint fp;

    sendFixedPoint(0, fp);
}

void bClient::_onLiveViewButtonPressed(void) {
    qDebug() << "liveView pressed!";

    socket->send("live_view", "toggle", 0);
}

void bClient::_onFocusUpButtonPressed(void) {
    qDebug() << "focusUp pressed!";

    socket->send("focus", "step", "up");
}

void bClient::_onFocusDownButtonPressed(void) {
    qDebug() << "focusDown pressed!";

    socket->send("focus", "step", "down");
}

void bClient::_onCaptureButtonPressed(void) {
    qDebug() << "capture pressed!";

    socket->send("shutter", "capture", "");
}

void bClient::_onTlRunButtonPressed(void) {
    qDebug() << "run TL pressed!";

    socket->send("timelapse", "toggle", "");
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

void bClient::_onLiveZoomSliderValueChanged(int val) {
     socket->send("live_view", "set_zoom", QString::number(val));
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

    if(dev=="live_view" && key=="status") {
        qDebug() << "lv: " << value;
        if (value=="on") {
            cg->setLVScene();
        }
        else {
            cg->setFPScene();
        }
    }

    if(dev=="motors" && key=="info") {
        mInfo.rangeMinPan = params[0].toInt();
        mInfo.rangeMaxPan = params[1].toInt();
        mInfo.rangeMinTilt = params[2].toInt();
        mInfo.rangeMaxTilt = params[3].toInt();

        cg->setRange(mInfo.rangeMinPan, mInfo.rangeMaxPan, mInfo.rangeMinTilt, mInfo.rangeMaxTilt);
        ui->panControl->setMinPosition(mInfo.rangeMinPan);
        ui->panControl->setMaxPosition(mInfo.rangeMaxPan);
        ui->tiltControl->setMinPosition(mInfo.rangeMinTilt);
        ui->tiltControl->setMaxPosition(mInfo.rangeMaxTilt);

        updateRangeLabel();
    }

    if(dev=="timelapse" && key=="status") {
        if(value=="1")ui->tlRunButton->setText("Stop");
        if(value=="0")ui->tlRunButton->setText("Run");
    }
}

void bClient::updateRangeLabel() {
    ui->labelRangePanTilt->setText(QString::number(mInfo.rangeMinPan) + "x" + QString::number(mInfo.rangeMaxPan) + " : " + QString::number(mInfo.rangeMinTilt) + "x" + QString::number(mInfo.rangeMaxTilt));
}
