#include "controlgraph.h"
#include <QDebug>

controlGraph::controlGraph(QWidget *parent) :
    QGraphicsView(parent)
{
    setRange(1000);

    scene.setSceneRect( 0.0, 0.0, parent->width(), parent->height() );
    setScene(&scene);

    lineTilt = new QGraphicsLineItem(0, &scene);
    lineTilt->setLine(0, 100.0, scene.width(), 100.0 );

    linePan = new QGraphicsLineItem(0, &scene);
    linePan->setLine(100.0, 0, 100.0, scene.height() );

    QGraphicsView( &scene, parent );
    setRenderHints( QPainter::Antialiasing );
    show();
}

void controlGraph::setRange(unsigned int r){
    range = r;
}

void controlGraph::_onPanPositionChanged(int value){
    setPanPosition(value);
}

void controlGraph::_onTiltPositionChanged(int value){
    setTiltPosition(value);
}

void controlGraph::setPanPosition(int value){
    float linePoint = 1.0 * value * scene.width() / range;
//    qDebug() << linePoint;
    linePan->setLine(linePoint, 0, linePoint, scene.width() );
}

void controlGraph::setTiltPosition(int value){
    float linePoint = 1.0 * value * scene.height() / range;
    lineTilt->setLine(0, linePoint, scene.height(), linePoint );
}

void controlGraph::mousePressEvent(QMouseEvent * event) {
    emit panPositionRequested(event->x() * range / scene.width());
    emit tiltPositionRequested(event->y() * range / scene.height());
}
