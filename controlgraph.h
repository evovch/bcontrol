#ifndef CONTROLGRAPH_H
#define CONTROLGRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>

#include "btypes.h"
#include "bgraphicsellipseitem.h"
#include "focuspoint.h"
#include "fastpixmapitem.h"

class controlGraph : public QGraphicsView
{
    Q_OBJECT
public:
    enum Mode {MODE_LIVEVIEW, MODE_VIEWFINDER_CAM};

    controlGraph(QWidget *parent = 0);

    fixedPointHash *fixedPoints;

    void setRange(unsigned int minX, unsigned int maxX, unsigned int minY, unsigned int maxY);

    void setFixedPoints(fixedPointHash *fp);
    void drawFixedPoints(void);

    void setPanPosition(int value);
    void setTiltPosition(int value);

    void setLVScene(Mode m);
    void setFPScene();

    QList<focusPoint *> getFocusPoints(void);
    void hightlightFocusPoint(int index);

    bool framerBusy;


    
private:
    QGraphicsScene scene;
    QGraphicsScene sceneLV;
    QGraphicsScene *currentScene;

    QGraphicsLineItem *lineTilt;
    QGraphicsLineItem *linePan;

    QList<focusPoint *> focusPoints;
    int activeFocusPointIndex;

    QHash<QString, bGraphicsEllipseItem*> elliseFixedPointHash;
    bool viewportEvent(QEvent *event);

    void mousePressEvent(QMouseEvent * event);

//    FastPixmapItem lvSnapshot;
    QGraphicsPixmapItem lvSnapshot;
    QGraphicsRectItem *fpPlot;
    unsigned char * currentFrameBuffer;

    void createFocusPoints(void);

    unsigned int rangeMinPan;
    unsigned int rangeMaxPan;
    unsigned int rangeMinTilt;
    unsigned int rangeMaxTilt;
    unsigned int visibleRangePan;
    unsigned int visibleRangeTilt;

signals:
    void panPositionRequested(int);
    void tiltPositionRequested(int);
    void touchMove(float, float);

public slots:
    void _onPanPositionChanged(int value);
    void _onTiltPositionChanged(int value);
    void _onFixedPointsUpdated(void);

    void _onGotAFrame(QByteArray frame);
    
public slots:
    
};

#endif // CONTROLGRAPH_H
