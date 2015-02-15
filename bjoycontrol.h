#ifndef BJOYCONTROL_H
#define BJOYCONTROL_H

#include <QObject>
#include "bsocket.h"
#include "controlgraph.h"
#include "liveviewsocket.h"

class bJoyControl : public QObject
{
    Q_OBJECT

private:
    bSocket *socket;

    controlGraph *cg;
    liveViewSocket *socketLv;

public:
    explicit bJoyControl(QObject *parent = 0);
    
signals:
    
public slots:
    void _onSpeedChangedX(int val);
    void _onSpeedChangedY(int val);
    void _onSpeedChangedZ(int val);
    
    void _onAfOn();
    void _onAfOff();
};

#endif // BJOYCONTROL_H
