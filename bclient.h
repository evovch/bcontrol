#ifndef BCLIENT_H
#define BCLIENT_H

#include <QObject>
#include "bsocket.h"
#include "ui_fhead.h"
#include "controlgraph.h"

class bClient : public QObject
{
    Q_OBJECT
public:
    explicit bClient(bSocket *socket, Ui_fhead *gui, QObject *parent = 0);

private:
    bSocket *socket;
    Ui_fhead *ui;
    controlGraph *cg;


signals:

public slots:
    void _onPanSpeedChanged(int value);
    void _onPanPositionChanged(int value);
    void _onDataReceived(QString, QString, QString);
};

#endif // BCLIENT_H
