#include "controlgraph.h"
#include <QDebug>
#include "bgraphicsellipseitem.h"

controlGraph::controlGraph(QWidget *parent) :
    QGraphicsView(parent)
{
    setRange(1000);

    setInteractive(true);

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
    linePan->setLine(linePoint, 0, linePoint, scene.height() );
}

void controlGraph::setTiltPosition(int value){
    float linePoint = 1.0 * value * scene.height() / range;
    lineTilt->setLine(0, scene.height()-linePoint, scene.width(), scene.height()-linePoint );
}

void controlGraph::mousePressEvent(QMouseEvent * event) {
    emit panPositionRequested(event->x() * range / scene.width());
    emit tiltPositionRequested((scene.height()-event->y()) * range / scene.height());
}

void controlGraph::setFixedPoints(fixedPointHash *fp) {
    fixedPoints = fp;
}

void controlGraph::_onFixedPointsUpdated(void){
    drawFixedPoints();
}

void controlGraph::drawFixedPoints() {
    QHash<QString, fixedPoint>::iterator i;
    QHash<QString, bGraphicsEllipseItem*>::iterator ii;

    for (ii = elliseFixedPointHash.begin(); ii != elliseFixedPointHash.end(); ++ii)delete ii.value();
    elliseFixedPointHash.clear();

    for (i = fixedPoints->begin(); i != fixedPoints->end(); ++i) {
        bGraphicsEllipseItem *e = new bGraphicsEllipseItem(0);
        scene.addItem(e);
        e->setRect(1.0 * i->panValue * scene.width() / range - 15, scene.height() - 1.0 * i->tiltValue * scene.height() / range - 15 , 30, 30 );

        QGraphicsSimpleTextItem *et = new QGraphicsSimpleTextItem(e);
        et->setPos(1.0 * i->panValue * scene.width() / range - 5, scene.height() - 1.0 * i->tiltValue * scene.height() / range - 14);
        et->setFont(QFont("Calibri", 20, QFont::Bold));

        et->setText(i->name);

        elliseFixedPointHash.insert(i.key(), e);
    }
}





