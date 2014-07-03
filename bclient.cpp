#include "bclient.h"
#include <QDebug>

bClient::bClient(QObject *parent) :
    QObject(parent)
{

    mw = new mainWindow();
    ui_mw = new Ui_mainWindow;
    ui_mw->setupUi(mw);

    mp = ui_mw->fheadTab;
    cam = ui_mw->camTab;

    ui_cam = new Ui_camera;
    ui_cam->setupUi(cam);

    ui = new Ui_fhead;
    ui->setupUi(mp);

    ui_mw->mwTabs->setCurrentIndex(0);
    mw->show();

    socket = new bSocket();
    socket->reconnect();

    socketLv = new liveViewSocket();
    socketLv->reconnect();

    cWatchTimer = new QTimer(this);
    connect(cWatchTimer, SIGNAL(timeout()), socket, SLOT(_onCWatchTimer()));
    connect(cWatchTimer, SIGNAL(timeout()), socketLv, SLOT(_onCWatchTimer()));
    cWatchTimer->start(1000);

    this->ui = ui;

    ui->captureButton->setFocus();

    fixedPoints = fixedPointHash();
    cg = new controlGraph(ui->headGraph);
    cg->setFixedPoints(&fixedPoints);

    fpModel = new bFixedPointModel(0, &fixedPoints);


    fpProxyModel = new QSortFilterProxyModel();
    fpProxyModel->setSourceModel( fpModel );
    fpProxyModel->setSortRole(Qt::InitialSortOrderRole);

    qDebug() << fpProxyModel->sortColumn();

    ui->fpTableView->setModel( fpProxyModel );

    dVals = new bCamParamModel(NULL, bCamParamModel::dMapId);
    ui_cam->camDCombo->setModel(dVals);
    ui_cam->camDCombo->setModelColumn(1);

    sVals = new bCamParamModel(NULL, bCamParamModel::sMapId);
    ui_cam->camSCombo->setModel(sVals);
    ui_cam->camSCombo->setModelColumn(1);

    modeVals = new bCamParamModel(NULL, bCamParamModel::modeMapId);
    ui_cam->camModeCombo->setModel(modeVals);
    ui_cam->camModeCombo->setModelColumn(1);

    afVals = new bCamParamModel(NULL, bCamParamModel::afMapId);
    ui_cam->camAfCombo->setModel(afVals);
    ui_cam->camAfCombo->setModelColumn(1);

    isoVals = new bCamParamModel(NULL, bCamParamModel::isoMapId);
    ui_cam->camIsoCombo->setModel(isoVals);
    ui_cam->camIsoCombo->setModelColumn(1);

    expVals = new bCamParamModel(NULL, bCamParamModel::expMapId);
    ui_cam->camExpCombo->setModel(expVals);
    ui_cam->camExpCombo->setModelColumn(1);


//    currentFixedPointId = "p1";
//    fpModel->selectFixedPoint(currentFixedPointId);

    QObject::connect(socketLv, SIGNAL(gotAFrame(QByteArray)), cg, SLOT(_onGotAFrame(QByteArray)));

    QObject::connect(ui->fpTableView, SIGNAL(pressed(QModelIndex)), fpModel, SLOT(_onCellClicked(QModelIndex)));

    QObject::connect(fpModel, SIGNAL(removeFixedPointClicked(QString)), this, SLOT(_onRemoveFixedPoint(QString)));
    QObject::connect(fpModel, SIGNAL(toggleTimelapseFixedPointClicked(QString)), this, SLOT(_onToggleTimelapseFixedPoint(QString)));
    QObject::connect(fpModel, SIGNAL(selectFixedPointClicked(QString)), this, SLOT(_onSelectFixedPoint(QString)));
    QObject::connect(fpModel, SIGNAL(selectRow(int)), ui->fpTableView, SLOT(selectRow(int)));

    QObject::connect(socket, SIGNAL(bConnected()), this, SLOT(_onConnected()));
    QObject::connect(socket, SIGNAL(bDisconnected()), this, SLOT(_onDisconnected()));

    ui->fpTableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->fpTableView->horizontalHeader()->resizeSection(0, 50);
    ui->fpTableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->fpTableView->horizontalHeader()->setResizeMode(2, QHeaderView::Fixed);
    ui->fpTableView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
    ui->fpTableView->horizontalHeader()->resizeSection(2, 25);
    ui->fpTableView->horizontalHeader()->resizeSection(3, 25);
    ui->fpTableView->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
    ui->fpTableView->horizontalHeader()->resizeSection(4, 0);

/*
    QObject::connect(ui_cam->camDCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamDIndexChanged(int)));
    QObject::connect(ui_cam->camSCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamSIndexChanged(int)));
    QObject::connect(ui_cam->camModeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamModeIndexChanged(int)));
    QObject::connect(ui_cam->camIsoCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamIsoIndexChanged(int)));
    QObject::connect(ui_cam->camExpCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamExpIndexChanged(int)));
    QObject::connect(ui_cam->camAfCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(_onCamAfIndexChanged(int)));
*/
    QObject::connect(ui_cam->camDSendButton, SIGNAL(pressed()), this, SLOT(_onCamDSendButtonPressed()));
    QObject::connect(ui_cam->camSSendButton, SIGNAL(pressed()), this, SLOT(_onCamSSendButtonPressed()));
    QObject::connect(ui_cam->camModeSendButton, SIGNAL(pressed()), this, SLOT(_onCamModeSendButtonPressed()));
    QObject::connect(ui_cam->camIsoSendButton, SIGNAL(pressed()), this, SLOT(_onCamIsoSendButtonPressed()));
    QObject::connect(ui_cam->camExpSendButton, SIGNAL(pressed()), this, SLOT(_onCamExpSendButtonPressed()));
    QObject::connect(ui_cam->camAfSendButton, SIGNAL(pressed()), this, SLOT(_onCamAfSendButtonPressed()));

    QObject::connect(ui->panControl, SIGNAL(speedChanged(int)), this, SLOT(_onPanSpeedChanged(int)));
    QObject::connect(ui->panControl, SIGNAL(positionChanged(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(ui->tiltControl, SIGNAL(speedChanged(int)), this, SLOT(_onTiltSpeedChanged(int)));
    QObject::connect(ui->tiltControl, SIGNAL(positionChanged(int)), this, SLOT(_onTiltPositionChanged(int)));

 //   QObject::connect(uimw, SIGNAL(virtualX(int)), this, SLOT(_onVirtualX(int)));
 //   QObject::connect(uimw, SIGNAL(virtualY(int)), this, SLOT(_onVirtualY(int)));

    QObject::connect(ui->panControl, SIGNAL(positionChanged(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(ui->tiltControl, SIGNAL(positionChanged(int)), this, SLOT(_onTiltPositionChanged(int)));

//    QObject::connect(mp, SIGNAL(afChanged(bool)), this, SLOT(_onAfChanged(bool)));
//    QObject::connect(mp, SIGNAL(srChanged(bool)), this, SLOT(_onSrChanged(bool)));
//    QObject::connect(mp, SIGNAL(afAndCaptureKey()), this, SLOT(_onCaptureButtonPressed()));
//    QObject::connect(mp, SIGNAL(fpPressed()), this, SLOT(_onFixedPointButtonPressed()));

    QObject::connect(ui->getFilesButton, SIGNAL(pressed()), this, SLOT(_onGetFilesButtonPressed()));
    QObject::connect(ui->fixedPointButton, SIGNAL(pressed()), this, SLOT(_onFixedPointButtonPressed()));

    QObject::connect(ui->liveViewZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(_onLiveZoomSliderValueChanged(int)));

    QObject::connect(ui->liveViewButton, SIGNAL(pressed()), this, SLOT(_onLiveViewButtonPressed()));
    QObject::connect(ui->focusUpButton, SIGNAL(pressed()), this, SLOT(_onFocusUpButtonPressed()));
    QObject::connect(ui->focusDownButton, SIGNAL(pressed()), this, SLOT(_onFocusDownButtonPressed()));

    QObject::connect(ui->captureButton, SIGNAL(pressed()), this, SLOT(_onCaptureButtonPressed()));

    QObject::connect(ui->tlRunButton, SIGNAL(pressed()), this, SLOT(_onTlRunButtonPressed()));
    QObject::connect(ui->tlDemoButton, SIGNAL(pressed()), this, SLOT(_onTlDemoButtonPressed()));

    QObject::connect(ui->flipPanButton, SIGNAL(pressed()), this, SLOT(_onFlipPanButtonPressed()));
    QObject::connect(ui->flipTiltButton, SIGNAL(pressed()), this, SLOT(_onFlipTiltButtonPressed()));

    QObject::connect(ui->setCenterButton, SIGNAL(pressed()), this, SLOT(_onSetCenterButtonPressed()));
    QObject::connect(ui->setNullButton, SIGNAL(pressed()), this, SLOT(_onSetNullButtonPressed()));

    QObject::connect(cg, SIGNAL(panPositionRequested(int)), this, SLOT(_onPanPositionChanged(int)));
    QObject::connect(cg, SIGNAL(tiltPositionRequested(int)), this, SLOT(_onTiltPositionChanged(int)));

    QObject::connect(cg, SIGNAL(touchMove(float, float)), this, SLOT(_onTouchMove(float, float)));

    QObject::connect(this, SIGNAL(fixedPointsUpdated()), cg, SLOT(_onFixedPointsUpdated()));
    QObject::connect(this, SIGNAL(fixedPointsUpdated()), fpModel, SLOT(_onFixedPointsUpdated()));
    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString,QStringList)), this, SLOT(_onDataReceived(QString,QString,QString,QStringList)));

}

void bClient::_onGetFilesButtonPressed(void) {
    qDebug() << "getFilesButton pressed!";

    socket->send("cam", "get_files", "");
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

void bClient::_onFlipPanButtonPressed(void) {
    qDebug() << "flipPan pressed!";

    socket->send("motor_pan", "flip_reverse", "");
}

void bClient::_onFlipTiltButtonPressed(void) {
    qDebug() << "flipTilt pressed!";

    socket->send("motor_tilt", "flip_reverse", "");
}



void bClient::_onTlRunButtonPressed(void) {
    qDebug() << "run TL pressed!";

    socket->send("timelapse", "set_delay", QString::number(ui->tlDelayInput->value()));
    socket->send("timelapse", "set_direction", QString::number(ui->tlDirectionInput->value()));
    socket->send("timelapse", "set_frames", QString::number(ui->tlFramesInput->value()));

    socket->send("timelapse", "toggle", "run");
}

void bClient::_onTlDemoButtonPressed(void) {
    qDebug() << "demo TL pressed!";

    socket->send("timelapse", "set_delay", QString::number(ui->tlDelayInput->value()));
    socket->send("timelapse", "set_direction", QString::number(ui->tlDirectionInput->value()));
    socket->send("timelapse", "set_frames", QString::number(ui->tlFramesInput->value()));

    socket->send("timelapse", "toggle", "demo");
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
    fpProxyModel->sort(4);
}


void bClient::_onPanSpeedChanged(int value) {
    socket->send("motor_pan", "set_speed", QString::number(value));

    qDebug() << "new Pan speed: " << value;
}

void bClient::_onPanPositionChanged(int value) {
    socket->send("motor_pan", "set_position", QString::number(value));
}

void bClient::_onTiltSpeedChanged(int value) {
    socket->send("motor_tilt", "set_speed", QString::number(value));

    qDebug() << "new Tilt speed: " << value;
}

void bClient::_onTouchMove(float valuePan, float valueTilt) {
    _onPanSpeedChanged(valuePan * 100 * 2);
    _onTiltSpeedChanged(valueTilt * -100 * 2);
}

void bClient::_onTiltPositionChanged(int value) {
    socket->send("motor_tilt", "set_position", QString::number(value));
}

void bClient::_onSetCenterButtonPressed(void) {
    socket->send("motor_pan", "set_center", "");
    socket->send("motor_tilt", "set_center", "");
}

void bClient::_onSetNullButtonPressed(void) {
    socket->send("motor_pan", "set_null", "");
    socket->send("motor_tilt", "set_null", "");
}

void bClient::_onRemoveFixedPoint(QString id) {
    socket->send("fixed_point", "remove", id);
}

void bClient::_onToggleTimelapseFixedPoint(QString id) {
    socket->send("fixed_point", "toggle_timelapse", id);
}

void bClient::_onSelectFixedPoint(QString id) {
     socket->send("fixed_point", "select", id);
}

void bClient::_onLiveZoomSliderValueChanged(int val) {
     socket->send("live_view", "set_zoom", QString::number(val));
}


void bClient::_onCamDIndexChanged(int val) {
     socket->send("cam", "set_d", dVals->getValue(val));

     qDebug() << "cam:set_d:" << dVals->getValue(val);
}

void bClient::_onCamSIndexChanged(int val) {
     socket->send("cam", "set_s", sVals->getValue(val));

     qDebug() << "cam:set_s:" << sVals->getValue(val);
}

void bClient::_onCamAfIndexChanged(int val) {
     socket->send("cam", "set_af", afVals->getValue(val));

     qDebug() << "cam:set_af:" << afVals->getValue(val);
}

void bClient::_onCamModeIndexChanged(int val) {
     socket->send("cam", "set_mode", modeVals->getValue(val));

     qDebug() << "cam:set_mode:" << modeVals->getValue(val);
}

void bClient::_onCamIsoIndexChanged(int val) {
     socket->send("cam", "set_iso", isoVals->getValue(val));

     qDebug() << "cam:set_iso:" << isoVals->getValue(val);
}

void bClient::_onCamExpIndexChanged(int val) {
     socket->send("cam", "set_exp", expVals->getValue(val));

     qDebug() << "cam:set_exp:" << expVals->getValue(val);
}


void bClient::_onCamDSendButtonPressed() {
     QString v = dVals->getValue(ui_cam->camDCombo->currentIndex());
     socket->send("cam", "set_d", v);

     qDebug() << "cam:set_d:" << v;
}

void bClient::_onCamSSendButtonPressed() {
     QString v = sVals->getValue(ui_cam->camSCombo->currentIndex());
     socket->send("cam", "set_s", v);

     qDebug() << "cam:set_s:" << v;
}

void bClient::_onCamModeSendButtonPressed() {
     QString v = modeVals->getValue(ui_cam->camModeCombo->currentIndex());
     socket->send("cam", "set_mode", v);

     qDebug() << "cam:set_mode:" << v;
}

void bClient::_onCamIsoSendButtonPressed() {
     QString v = isoVals->getValue(ui_cam->camIsoCombo->currentIndex());
     socket->send("cam", "set_iso", v);

     qDebug() << "cam:set_iso:" << v;
}

void bClient::_onCamExpSendButtonPressed() {
     QString v = expVals->getValue(ui_cam->camExpCombo->currentIndex());
     socket->send("cam", "set_exp", v);

     qDebug() << "cam:set_exp:" << v;
}

void bClient::_onCamAfSendButtonPressed() {
     QString v = afVals->getValue(ui_cam->camAfCombo->currentIndex());
     socket->send("cam", "set_af", v);

     qDebug() << "cam:set_af:" << v;
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
        p.timelapseMember = params[3].toInt();

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
//        qDebug() << "lv: " << value;
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

    if(dev=="timelapse") {
//        qDebug() << key << value;
        if(key=="status"){
            if(value=="1"){
                ui->tlRunButton->setText("Stop");
                ui->tlDemoButton->setText("Stop");
            }
            if(value=="0"){
                ui->tlRunButton->setText("Run");
                ui->tlDemoButton->setText("Demo");
            }
        }
        if(key=="progress")ui->tlProgress->setValue(value.toInt());
    }

    if(dev=="cam") {
//        qDebug() << "cam key: " << key;
        if(key=="current_d" && !ui_cam->camDCombo->hasFocus())ui_cam->camDCombo->setCurrentIndex(dVals->getIndex(value));
        if(key=="current_s" && !ui_cam->camSCombo->hasFocus())ui_cam->camSCombo->setCurrentIndex(sVals->getIndex(value));
        if(key=="current_af" && !ui_cam->camAfCombo->hasFocus())ui_cam->camAfCombo->setCurrentIndex(afVals->getIndex(value));
        if(key=="current_mode" && !ui_cam->camModeCombo->hasFocus())ui_cam->camModeCombo->setCurrentIndex(modeVals->getIndex(value));
        if(key=="current_iso" && !ui_cam->camIsoCombo->hasFocus())ui_cam->camIsoCombo->setCurrentIndex(isoVals->getIndex(value));
        if(key=="current_exp" && !ui_cam->camExpCombo->hasFocus())ui_cam->camExpCombo->setCurrentIndex(expVals->getIndex(value));
    }
}

void bClient::updateRangeLabel() {
    ui->labelRangePanTilt->setText(QString::number(mInfo.rangeMinPan) + "x" + QString::number(mInfo.rangeMaxPan) + " : " + QString::number(mInfo.rangeMinTilt) + "x" + QString::number(mInfo.rangeMaxTilt));
}

void bClient::_onVirtualX(int val) {
    if(val > 4500 && val < 5500) {
        _onPanSpeedChanged(0);
        return;
    }
    _onPanSpeedChanged((val - 5000) / 50);
}

void bClient::_onVirtualY(int val) {
    if(val > 4500 && val < 5500) {
        _onTiltSpeedChanged(0);
        return;
    }
    _onTiltSpeedChanged((val - 5000) / 50);
}

void bClient::_onConnected() {
    mw->statusBar()->showMessage("Connected", 0);
}

void bClient::_onDisconnected() {
    mw->statusBar()->showMessage("Disconnected", 0);
}

void bClient::_onAfChanged(bool s) {
    if(s==true)socket->send("cam", "af_trigger", "1");
    else socket->send("cam", "af_trigger", "0");

    qDebug() << "sending AF: " << s;
}

void bClient::_onSrChanged(bool s) {
    if(s==true)socket->send("cam", "sr_trigger", "1");
    else socket->send("cam", "sr_trigger", "0");

    qDebug() << "sending SR: " << s;
}

