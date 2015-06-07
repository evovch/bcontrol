#include "bjoycontrol.h"
#include "mainBox.h"
#include <QDebug>
#include <QTimer>

bJoyControl::bJoyControl(QObject *parent) :
    QObject(parent)
{
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
    socket->send("motor_pan", "set_speed", QString::number(val));
    qDebug() << "new Pan speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedY(int val) {
    socket->send("motor_tilt", "set_speed", QString::number(val));
    qDebug() << "new Tilt speed by bJoy: " << val;
}

void bJoyControl::_onSpeedChangedZ(int val) {
    socket->send("motor_ziim", "set_speed", QString::number(val));
    qDebug() << "new Zoom speed by bJoy: " << val;
}

void bJoyControl::_onGpioEdge(unsigned int gpioNum, bool level) {
    if(gpioNum == 67 && level == false)socket->send("live_view", "toggle", 0);
    else if(gpioNum == 2)_onSrChanged(level);
    else if(gpioNum == 4)_onAfChanged(level);

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
