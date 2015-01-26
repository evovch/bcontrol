#ifndef BJOYCONTROL_H
#define BJOYCONTROL_H

#include <QObject>
#include "bsocket.h"

class bJoyControl : public QObject
{
    Q_OBJECT

private:
    bSocket *socket;

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
