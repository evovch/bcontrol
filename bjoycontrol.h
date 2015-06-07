#ifndef BJOYCONTROL_H
#define BJOYCONTROL_H

#include <QObject>
#include "bsocket.h"
#include "controlgraph.h"
#include "liveviewsocket.h"
#include "btypes.h"
#include "gpioint.h"

class bJoyControl : public QObject
{
    Q_OBJECT

private:
    bSocket *socket;

    controlGraph *cg;
    liveViewSocket *socketLv;

    gpioInt *led2Gpio, *led3Gpio;

//    bFixedPointModel *fpModel;
//    QSortFilterProxyModel *fpProxyModel;

    fixedPointHash fixedPoints;
    QString currentFixedPointId;

    motorsInfo mInfo;

    QTimer *cWatchTimer;

public:
    explicit bJoyControl(QObject *parent = 0);

    void addFixedPoint(QString id, fixedPoint fp);
    void removeFixedPoint(QString id);

    void sendFixedPoint(QString id, fixedPoint fp);
    void clearFixedPoints(void);
    void refreshFixedPoints(void);
    
signals:
    void fixedPointsUpdated(void);
    
public slots:
    void _onSpeedChangedX(int val);
    void _onSpeedChangedY(int val);
    void _onSpeedChangedZ(int val);

    void _onDataReceived(QString dev, QString key, QString value, QStringList params);
    
    void _onGpioEdge(unsigned int gpioNum, bool level);

    void _onConnected(void);
    void _onDisonnected(void);

    void _onAfChanged(bool s);
    void _onSrChanged(bool s);
};

#endif // BJOYCONTROL_H
