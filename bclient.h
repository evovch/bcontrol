#ifndef BCLIENT_H
#define BCLIENT_H

#include <QObject>
#include "bsocket.h"
#include "liveviewsocket.h"
#include "ui_fhead.h"
#include "controlgraph.h"
#include <QStringList>
#include "btypes.h"
#include "bfixedpointmodel.h"

class bClient : public QObject
{
    Q_OBJECT

public:
    explicit bClient(Ui_fhead *gui, QObject *parent = 0);

    void addFixedPoint(QString id, fixedPoint fp);
    void removeFixedPoint(QString id);

    void sendFixedPoint(QString id, fixedPoint fp);
    void clearFixedPoints(void);
    void refreshFixedPoints(void);

private:
    bSocket *socket;
    liveViewSocket *socketLv;
    Ui_fhead *ui;
    controlGraph *cg;

    bFixedPointModel *fpModel;



    fixedPointHash fixedPoints;
    QString currentFixedPointId;

    typedef struct {
        int rangeMinPan;
        int rangeMaxPan;
        int rangeMinTilt;
        int rangeMaxTilt;
    } motorsInfo;

    motorsInfo mInfo;

    void updateRangeLabel();

signals:
    void fixedPointsUpdated(void);

public slots:
    void _onPanSpeedChanged(int value);
    void _onPanPositionChanged(int value);
    void _onTiltSpeedChanged(int value);
    void _onTiltPositionChanged(int value);

    void _onRemoveFixedPoint(QString id);
    void _onSelectFixedPoint(QString id);

    void _onDataReceived(QString, QString, QString, QStringList params);

    void _onFixedPointButtonPressed(void);
    void _onLiveViewButtonPressed(void);
    void _onFocusUpButtonPressed(void);
    void _onFocusDownButtonPressed(void);
    void _onCaptureButtonPressed(void);

    void _onLiveZoomSliderValueChanged(int val);
};

#endif // BCLIENT_H
