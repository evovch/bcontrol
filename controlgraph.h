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

    void setRange(unsigned int r);

    void setFixedPoints(fixedPointHash *fp);
    void drawFixedPoints(void);

    void setPanPosition(int value);
    void setTiltPosition(int value);

    
private:
    QGraphicsScene scene;
    QGraphicsLineItem *lineTilt;
    QGraphicsLineItem *linePan;

    QHash<QString, bGraphicsEllipseItem*> elliseFixedPointHash;

    void mousePressEvent(QMouseEvent * event);

    unsigned int range;



signals:
    void panPositionRequested(int);
    void tiltPositionRequested(int);

public slots:
    void _onPanPositionChanged(int value);
    void _onTiltPositionChanged(int value);
    void _onFixedPointsUpdated(void);
    
public slots:
    
};

#endif // CONTROLGRAPH_H
