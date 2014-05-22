#ifndef CONTROLGRAPH_H
#define CONTROLGRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>

#include "btypes.h"
#include "bgraphicsellipseitem.h";

class controlGraph : public QGraphicsView
{
    Q_OBJECT
public:
    controlGraph(QWidget *parent = 0);

    fixedPointHash *fixedPoints;

    void setRange(unsigned int minX, unsigned int maxX, unsigned int minY, unsigned int maxY);

    void setFixedPoints(fixedPointHash *fp);
    void drawFixedPoints(void);

    void setPanPosition(int value);
    void setTiltPosition(int value);

    void setLVScene();
    void setFPScene();
    
private:
    QGraphicsScene scene;
    QGraphicsScene sceneLV;
    QGraphicsScene *currentScene;

    QGraphicsLineItem *lineTilt;
    QGraphicsLineItem *linePan;

    QHash<QString, bGraphicsEllipseItem*> elliseFixedPointHash;

    void mousePressEvent(QMouseEvent * event);

    QGraphicsPixmapItem lvSnapshot;

    unsigned int rangeMinPan;
    unsigned int rangeMaxPan;
    unsigned int rangeMinTilt;
    unsigned int rangeMaxTilt;
    unsigned int visibleRangePan;
    unsigned int visibleRangeTilt;

signals:
    void panPositionRequested(int);
    void tiltPositionRequested(int);

public slots:
    void _onPanPositionChanged(int value);
    void _onTiltPositionChanged(int value);
    void _onFixedPointsUpdated(void);

    void _onGotAFrame(QByteArray frame);
    
public slots:
    
};

#endif // CONTROLGRAPH_H
