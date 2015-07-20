#include "bjoycontrol.h"
#include "mainBox.h"
#include <QDebug>
#include <QTimer>

#define BUTTON_FLIPZOOM 68
#define BUTTON_FLIPFOCUS 69
#define BUTTON_FLIPPAN 15
#define BUTTON_FLIPTILT 27
#define BUTTON_ZOOMIN 49
#define BUTTON_ZOOMOUT 22

#define BUTTON_FPMEM 61
#define BUTTON_FP1 65
#define BUTTON_FP2 14
#define BUTTON_FP3 46
#define BUTTON_FP4 23
#define BUTTON_FP5 10011

#define BUTTON_PANRESET 50
#define BUTTON_TILTRESET 51
#define BUTTON_PANNULL 48
#define BUTTON_TILTNULL 26
#define BUTTON_PANLIMIT 5
#define BUTTON_TILTLIMIT 47

#define BUTTON_LIVEVIEW 1160
#define BUTTON_FINEMODE 116
#define BUTTON_SR 2
#define BUTTON_AF 4

bJoyControl::bJoyControl(QObject *parent) :
    QObject(parent)
{
    fpMemoryOnStatus = false;
    fineMode = false;

    mainBox *mb = new mainBox();
    mb->show();

    cg = new controlGraph(mb);
    fixedPoints = fixedPointHash();
    cg->setFixedPoints(&fixedPoints);
    cg->setFPScene();

    socketLv = new liveViewSocket();
    socketLv->reconnect();

    QObject::connect(socketLv, SIGNAL(gotAFrame(QByteArray)), cg, SLOT(_onGotAFrame(QByteArray)));

    socket = new bSocket();
    socket->reconnect();

    led2Gpio = new gpioInt(66);
    led3Gpio = new gpioInt(67);
    led2Gpio->setOutput();
    led3Gpio->setOutput();
    led2Gpio->setValue(1);
    led3Gpio->setValue(0);

    QObject::connect(socket, SIGNAL(bConnected()), this, SLOT(_onConnected()));
    QObject::connect(socket, SIGNAL(bDisonnected()), this, SLOT(_onDisonnected()));

    QObject::connect(socket, SIGNAL(dataReceived(QString,QString,QString,QStringList)), this, SLOT(_onDataReceived(QString,QString,QString,QStringList)));
    QObject::connect(this, SIGNAL(fixedPointsUpdated()), cg, SLOT(_onFixedPointsUpdated()));

    cWatchTimer = new QTimer(this);
    connect(cWatchTimer, SIGNAL(timeout()), socket, SLOT(_onCWatchTimer()));
    connect(cWatchTimer, SIGNAL(timeout()), socketLv, SLOT(_onCWatchTimer()));
    cWatchTimer->start(1000);
}

void bJoyControl::_onSpeedChangedX(int val) {
    if(fineMode)val = val/10;
    socket->send("motor_pan", "set_speed", QString::number(val));
    qDebug() << "new Pan speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedY(int val) {
    if(fineMode)val = val/10;
    socket->send("motor_tilt", "set_speed", QString::number(val));
    qDebug() << "new Tilt speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedZ(int val) {
    if(fineMode)val = val/10;
    socket->send("motor_zoom", "set_speed", QString::number(val));
    qDebug() << "new Zoom speed by bJoy: " << val;
}

void bJoyControl::_onGpioEdge(unsigned int gpioNum, bool level) {
    switch ( gpioNum ) {
        case BUTTON_LIVEVIEW:
          if(level == false)socket->send("live_view", "toggle", 0);
          break;

        case BUTTON_SR:
          _onSrChanged(level);
          break;

        case BUTTON_AF:
          _onAfChanged(level);
          break;

        case BUTTON_ZOOMIN:
            _onZoomInChanged(level);
            break;

        case BUTTON_ZOOMOUT:
            _onZoomOutChanged(level);
            break;

        case BUTTON_FLIPPAN:
            if(level == false)socket->send("motor_pan", "flip_reverse", "");
            break;

        case BUTTON_FLIPTILT:
            if(level == false)socket->send("motor_tilt", "flip_reverse", "");
            break;

        case BUTTON_FLIPZOOM:
            if(level == false)socket->send("motor_zoom", "flip_reverse", "");
            break;

        case BUTTON_FLIPFOCUS:
            if(level == false)socket->send("motor_focus", "flip_reverse", "");
            break;

        case BUTTON_FPMEM:
            fpMemoryOnStatus = false;
            if(level == true)fpMemoryOnStatus = true;
            qDebug() << "fpMemoryOnStatus set: " << fpMemoryOnStatus;
            break;

        case BUTTON_FINEMODE:
            fineMode = false;
            if(level == true)fineMode = true;
            break;

        case BUTTON_FP1:
            if(level == false)_onFixedPointButtonPressed(1);
            break;

        case BUTTON_FP2:
            if(level == false)_onFixedPointButtonPressed(2);
            break;

        case BUTTON_FP3:
            if(level == false)_onFixedPointButtonPressed(3);
            break;

        case BUTTON_FP4:
            if(level == false)_onFixedPointButtonPressed(4);
            break;

        case BUTTON_FP5:
            if(level == false)_onFixedPointButtonPressed(5);
            break;

        case BUTTON_PANRESET:
            if(level == false)_onPanResetButtonPressed();
            break;

        case BUTTON_TILTRESET:
            if(level == false)_onTiltResetButtonPressed();
            break;

        case BUTTON_PANNULL:
            if(level == false)_onPanNullButtonPressed();
            break;

        case BUTTON_TILTNULL:
            if(level == false)_onTiltNullButtonPressed();
            break;

        case BUTTON_PANLIMIT:
            if(level == false)_onPanLimitButtonPressed();
            break;

        case BUTTON_TILTLIMIT:
            if(level == false)_onTiltLimitButtonPressed();
            break;

        default:
              qDebug() << "button not assgned. gpio: " << gpioNum;
              break;
    }

    qDebug() << "gpioNum: " << gpioNum << "=" << level;
}

void bJoyControl::_onDataReceived(QString dev, QString key, QString value, QStringList params) {
    if(dev=="motor_pan" && key=="status_position") {
        cg->setPanPosition(value.toInt());
    }

    if(dev=="motor_tilt" && key=="status_position") {
        cg->setTiltPosition(value.toInt());
    }

    if(dev=="live_view" && key=="status") {
        if (value=="on") {
            cg->setLVScene();
        }
        else {
            cg->setFPScene();
        }
    }

    if(dev=="fixed_point" && key=="get") {
        removeFixedPoint(value);

        fixedPoint p;
        p.name = params[0];
        p.timelapseMember = params[1].toInt();
        p.panValue = params[2].toInt();
        p.tiltValue = params[3].toInt();
        p.zoomValue = params[4].toInt();
        p.focusValue = params[5].toInt();
        p.sliderValue = params[6].toInt();

        addFixedPoint(value, p);
    }

    if(dev=="fixed_point" && key=="clear") {
        clearFixedPoints();
    }

    if(dev=="fixed_point" && key=="refresh") {
        refreshFixedPoints();
    }

    if(dev=="motors" && key=="info") {
        mInfo.rangeMinPan = params[0].toInt();
        mInfo.rangeMaxPan = params[1].toInt();
        mInfo.rangeMinTilt = params[2].toInt();
        mInfo.rangeMaxTilt = params[3].toInt();
        mInfo.rangeMinZoom = params[4].toInt();
        mInfo.rangeMaxZoom = params[5].toInt();
        mInfo.rangeMinFocus = params[6].toInt();
        mInfo.rangeMaxFocus = params[7].toInt();
        mInfo.rangeMinSlider = params[8].toInt();
        mInfo.rangeMaxSlider = params[9].toInt();

        cg->setRange(mInfo.rangeMinPan, mInfo.rangeMaxPan, mInfo.rangeMinTilt, mInfo.rangeMaxTilt);
    }
}

void bJoyControl::sendFixedPoint(QString id, fixedPoint fp) {
    QStringList params;
    params.append(fp.name);

    socket->send("fixed_point", "set_current", id,  params);
}

void bJoyControl::addFixedPoint(QString id, fixedPoint fp) {
    fixedPoints.insert(id, fp);
}

void bJoyControl::removeFixedPoint(QString id) {
    if(fixedPoints.find(id)==fixedPoints.end())return;

    fixedPoints.remove(id);
}

void bJoyControl::clearFixedPoints(void) {
    fixedPoints.clear();
}

void bJoyControl::refreshFixedPoints(void) {
    emit fixedPointsUpdated();
}

void bJoyControl::_onConnected(void) {
    led3Gpio->setValue(1);
}

void bJoyControl::_onDisonnected(void) {
    led3Gpio->setValue(0);
}

void bJoyControl::_onAfChanged(bool s) {
    if(s==true)socket->send("cam", "af_trigger", "1");
    else socket->send("cam", "af_trigger", "0");

    qDebug() << "sending AF: " << s;
}

void bJoyControl::_onSrChanged(bool s) {
    if(s==true)socket->send("cam", "sr_trigger", "1");
    else socket->send("cam", "sr_trigger", "0");

    qDebug() << "sending SR: " << s;
}

void bJoyControl::_onZoomInChanged(bool s) {
    int speed = 0;
    if(s==true)speed=100;
    socket->send("motor_zoom", "set_speed", QString::number(speed));

    qDebug() << "new Zoom speed: " << speed;
}

void bJoyControl::_onZoomOutChanged(bool s) {
    int speed = 0;
    if(s==true)speed=-100;

    socket->send("motor_zoom", "set_speed", QString::number(speed));

    qDebug() << "new Zoom speed: " << speed;
}

void bJoyControl::_onFixedPointButtonPressed(int buttonNum) {
    QString id = "bj_" + QString::number(buttonNum);

    qDebug() << "fpMemoryOnStatus: " << fpMemoryOnStatus;
    if(fpMemoryOnStatus==true) {
        socket->send("fixed_point", "set_current", id);
    }
    else {
        socket->send("fixed_point", "select", id);
    }
}

void bJoyControl::_onPanResetButtonPressed() {
    if(fpMemoryOnStatus==false) {
        socket->send("motor_pan", "reset_limit", "");
        socket->send("motor_pan", "set_center", "");
    }
    else {
        socket->send("motor_zoom", "reset_limit", "");
        socket->send("motor_zoom", "set_center", "");
    }
}

void bJoyControl::_onTiltResetButtonPressed() {
    if(fpMemoryOnStatus==false) {
        socket->send("motor_tilt", "reset_limit", "");
        socket->send("motor_tilt", "set_center", "");
    }
    else {
        socket->send("motor_focus", "reset_limit", "");
        socket->send("motor_focus", "set_center", "");
    }
}

void bJoyControl::_onPanNullButtonPressed() {
    if(fpMemoryOnStatus==false) {
        socket->send("motor_pan", "set_null", "");
    }
    else {
        socket->send("motor_zoom", "set_null", "");
    }
}

void bJoyControl::_onTiltNullButtonPressed() {
    if(fpMemoryOnStatus==false) {
      socket->send("motor_tilt", "set_null", "");
    }
    else {
      socket->send("motor_focus", "set_null", "");
    }
}

void bJoyControl::_onPanLimitButtonPressed() {
    if(fpMemoryOnStatus==false) {
      socket->send("motor_pan", "set_limit", "");
    }
    else {
      socket->send("motor_zoom", "set_limit", "");
    }
}

void bJoyControl::_onTiltLimitButtonPressed() {
    if(fpMemoryOnStatus==false) {
      socket->send("motor_tilt", "set_limit", "");
    }
    else {
      socket->send("motor_focus", "set_limit", "");
    }
}

