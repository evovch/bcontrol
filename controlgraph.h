#ifndef CONTROLGRAPH_H
#define CONTROLGRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>

class controlGraph : public QGraphicsView
{
    Q_OBJECT
public:
    controlGraph(QWidget *parent = 0);

    void setRange(unsigned int r);

    void setPanPosition(int value);
    void setTiltPosition(int value);

    
private:
    QGraphicsScene scene;
    QGraphicsLineItem *lineTilt;
    QGraphicsLineItem *linePan;

    void mousePressEvent(QMouseEvent * event);

    unsigned int range;

signals:
    void panPositionRequested(int);
    void tiltPositionRequested(int);

public slots:
    void _onPanPositionChanged(int value);
    void _onTiltPositionChanged(int value);
    
public slots:
    
};

#endif // CONTROLGRAPH_H
