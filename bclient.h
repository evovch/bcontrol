#ifndef BCLIENT_H
#define BCLIENT_H

#include <QObject>
#include "bsocket.h"
#include "liveviewsocket.h"
#include "ui_fhead.h"
#include "ui_mainwindow.h"
#include "ui_camera.h"
#include "ui_timelapse.h"
#include "ui_limitswindow.h"
#include "ui_network.h"
#include "mainwindow.h"
#include "controlgraph.h"
#include <QStringList>
#include "btypes.h"
#include "bfixedpointmodel.h"
#include "bcamparammodel.h"

class bClient : public QObject
{
    Q_OBJECT

public:
    explicit bClient(QObject *parent = 0);

    void addFixedPoint(QString id, fixedPoint fp);
    void removeFixedPoint(QString id);

    void sendFixedPoint(QString id, fixedPoint fp);
    void clearFixedPoints(void);
    void refreshFixedPoints(void);

private:
    bSocket *socket;
    liveViewSocket *socketLv;
    Ui_fhead *ui;
    Ui_camera *ui_cam;
    Ui_mainWindow *ui_mw;
    Ui_timelapse *ui_tl;
    Ui_limitsWindow *ui_lw;
    Ui_network *ui_nw;
    controlGraph *cg;

    QDialog *limitsWindow;

    fhead *mp;
    camera *cam;
    timelapse *tl;
    mainWindow *mw;
    network *nw;


    bFixedPointModel *fpModel;
    QSortFilterProxyModel *fpProxyModel;

    QTimer *cWatchTimer;

    bCamParamModel *sVals;
    bCamParamModel *dVals;
    bCamParamModel *modeVals;
    bCamParamModel *afVals;
    bCamParamModel *isoVals;
    bCamParamModel *expVals;

    fixedPointHash fixedPoints;
    QString currentFixedPointId;

    typedef struct {
        int rangeMinPan;
        int rangeMaxPan;
        int rangeMinTilt;
        int rangeMaxTilt;
        int rangeMinFocus;
        int rangeMaxFocus;
        int rangeMinZoom;
        int rangeMaxZoom;

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
    void _onZoomPositionChanged(int value);
    void _onZoomSpeedChanged(int value);
    void _onFocusPositionChanged(int value);
    void _onFocusSpeedChanged(int value);

    void _onTouchMove(float valuePan, float valueTilt);

    void _onRemoveFixedPoint(QString id);
    void _onSelectFixedPoint(QString id);

    void _onDataReceived(QString, QString, QString, QStringList params);

    void _onFixedPointButtonPressed(void);
    void _onLiveViewButtonPressed(void);
    void _onFocusUpButtonPressed(void);
    void _onFocusDownButtonPressed(void);
    void _onFocusUpMuchButtonPressed(void);
    void _onFocusDownMuchButtonPressed(void);

    void _onFocusPointPressed(int id);

    void _onCaptureButtonPressed(void);

    void _onFocusValue(int);

    void _onTlRunButtonPressed(void);
    void _onTlDemoButtonPressed(void);
    void _onToggleTimelapseFixedPoint(QString id);

    void _onSetCenterButtonPressed(void);
    void _onSetNullButtonPressed(void);

    void _onLiveZoomSliderValueChanged(int val);

    void _onCamDIndexChanged(int val);
    void _onCamSIndexChanged(int val);
    void _onCamAfIndexChanged(int val);
    void _onCamModeIndexChanged(int val);
    void _onCamIsoIndexChanged(int val);
    void _onCamExpIndexChanged(int val);

    void _onCamDSendButtonPressed();
    void _onCamSSendButtonPressed();
    void _onCamModeSendButtonPressed();
    void _onCamAfSendButtonPressed();
    void _onCamIsoSendButtonPressed();
    void _onCamExpSendButtonPressed();

    void _onFlipPanButtonPressed(void);
    void _onFlipTiltButtonPressed(void);

    void _onPopupLimitsButtonPressed();

    void _onVirtualX(int val);
    void _onVirtualY(int val);

    void _onConnected(void);
    void _onDisconnected(void);

    void _onAfChanged(bool);
    void _onSrChanged(bool);

    void _onGetFilesButtonPressed(void);

    void _onDoSeek(QString name, int pos);
    void _onDoSetNull(QString name);
    void _onDoSetCenter(QString name);
    void _onDoSetLimit(QString name);
    void _onDoResetLimit(QString name);

    void _onFlipZoomButtonPressed(void);
    void _onFlipFocusButtonPressed(void);
    void _onSetCenterZFButtonPressed(void);
    void _onSetNullZFButtonPressed(void);

    void _onReconnectButtonPressed();
};

#endif // BCLIENT_H
