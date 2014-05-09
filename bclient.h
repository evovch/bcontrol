#ifndef BCLIENT_H
#define BCLIENT_H

#include <QObject>
#include "bsocket.h"
#include "ui_fhead.h"
#include "controlgraph.h"
#include <QStringList>
#include "btypes.h"

class bClient : public QObject
{
    Q_OBJECT

public:
    explicit bClient(bSocket *socket, Ui_fhead *gui, QObject *parent = 0);

    void addFixedPoint(QString id, fixedPoint fp);
    void removeFixedPoint(QString id);

    void sendFixedPoint(QString id, fixedPoint fp);
    void clearFixedPoints(void);
    void refreshFixedPoints(void);

private:
    bSocket *socket;
    Ui_fhead *ui;
    controlGraph *cg;

    fixedPointHash fixedPoints;

signals:
    void fixedPointsUpdated(void);

public slots:
    void _onPanSpeedChanged(int value);
    void _onPanPositionChanged(int value);
    void _onTiltSpeedChanged(int value);
    void _onTiltPositionChanged(int value);

    void _onDataReceived(QString, QString, QString, QStringList params);

    void _onfixedPointButtonPressed(void);
};

#endif // BCLIENT_H
