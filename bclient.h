#ifndef BCLIENT_H
#define BCLIENT_H

#include <QObject>
#include "bsocket.h"
#include "ui_fhead.h"
#include "controlgraph.h"
#include <QStringList>

class bClient : public QObject
{
    Q_OBJECT

public:
    explicit bClient(bSocket *socket, Ui_fhead *gui, QObject *parent = 0);

    void addFixedPoint(QString id, controlGraph::fixedPoint fp);
    void removeFixedPoint(QString id);

private:
    bSocket *socket;
    Ui_fhead *ui;
    controlGraph *cg;

    controlGraph::fixedPointHash fixedPoints;

signals:
    void fixedPointsUpdated(void);

public slots:
    void _onPanSpeedChanged(int value);
    void _onPanPositionChanged(int value);
    void _onDataReceived(QString, QString, QString, QStringList params);
};

#endif // BCLIENT_H
