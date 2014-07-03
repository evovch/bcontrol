#include "controlgraph.h"
#include <QDebug>
#include "bgraphicsellipseitem.h"

controlGraph::controlGraph(QWidget *parent) :
    QGraphicsView(parent)
{
    setRange(0, 0, 1000, 1000);

    setInteractive(true);

    scene.setSceneRect( 0.0, 0.0, parent->width(), parent->height() );
    setScene(&scene);

    lineTilt = new QGraphicsLineItem(0, &scene);
    lineTilt->setLine(0, 100.0, scene.width(), 100.0 );
    lineTilt->setZValue(2);

    linePan = new QGraphicsLineItem(0, &scene);
    linePan->setLine(100.0, 0, 100.0, scene.height() );
    linePan->setZValue(2);

    QGraphicsView( &scene, parent );
    setRenderHints( QPainter::Antialiasing );
    show();

    sceneLV.setSceneRect( 0.0, 0.0, parent->width(), parent->height() );

    QImage img(parent->width(), parent->height(), QImage::Format_RGB32);
    img.load("/Users/korytov/snowww.jpg");
    QPixmap pm = QPixmap::fromImage(img);
    pm = pm.scaled(sceneLV.width(), sceneLV.height(),  Qt::KeepAspectRatio, Qt::SmoothTransformation);

    lvSnapshot.setPixmap(pm);
    sceneLV.addItem(&lvSnapshot);

    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
}

bool controlGraph::viewportEvent(QEvent *event)
{
    QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
    switch (event->type()) {
    case QEvent::TouchBegin: {
        qDebug() << "touch TouchBegin";
        return true;
    }

    case QEvent::TouchUpdate: {
        qDebug() << "touch TouchUpdate";
        const QTouchEvent::TouchPoint &touchPoint0 = touchEvent->touchPoints().first();

        int s = 2;
        if(touchEvent->touchPoints().size()==3)s = 5;

        float deltaX = touchPoint0.normalizedPos().x() - touchPoint0.startNormalizedPos().x();
        float deltaY = touchPoint0.normalizedPos().y() - touchPoint0.startNormalizedPos().y();
 //       if(deltaX > -0.01 && deltaX < 0.01)deltaX=0;
 //       if(deltaY > -0.01 && deltaY < 0.01)deltaY=0;
        emit touchMove(deltaX/s, deltaY/s);

        return true;
    }
    case QEvent::TouchEnd:
    {
        emit touchMove(0, 0);

        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void controlGraph::setLVScene() {
    if (currentScene == &sceneLV)return;
    currentScene = &sceneLV;
    setScene(&sceneLV);
}

void controlGraph::setFPScene() {
    if (currentScene == &scene)return;
    currentScene = &scene;
    setScene(&scene);
}

void controlGraph::_onGotAFrame(QByteArray frame) {
//    qDebug() << "got new frame: " << frame.size();

    QImage i;
    if (!i.loadFromData(frame, "JPEG")){
        /*
        QFile file("/Users/korytov/2/corrupted2.jpg");
        file.open(QIODevice::WriteOnly);
        file.write(frame);
        file.close();
*/
        return;
    }
/*
    QFile file2("/Users/korytov/2/correct2.jpg");
    file2.open(QIODevice::WriteOnly);
    file2.write(frame);
    file2.close();
*/
    lvSnapshot.setPixmap(QPixmap::fromImage(i).scaled(sceneLV.width(), sceneLV.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

//    qDebug() << i.size().width();
}

void controlGraph::setRange(unsigned int minX, unsigned int maxX, unsigned int minY, unsigned int maxY){
    rangeMinPan = minX;
    rangeMaxPan = maxX;
    rangeMinTilt = minY;
    rangeMaxTilt = maxY;

    visibleRangePan = maxX - minX;
    visibleRangeTilt = maxY - minY;
}

void controlGraph::_onPanPositionChanged(int value){
    setPanPosition(value);
}

void controlGraph::_onTiltPositionChanged(int value){
    setTiltPosition(value);
}

void controlGraph::setPanPosition(int value){
    float linePoint = 1.0 * (value -  rangeMinPan) * scene.width() / visibleRangePan;
    linePan->setLine(linePoint, 0, linePoint, scene.height() );
}

void controlGraph::setTiltPosition(int value){
    float linePoint = 1.0 * (value - rangeMinTilt) * scene.height() / visibleRangeTilt;
    lineTilt->setLine(0, scene.height()-linePoint, scene.width(), scene.height()-linePoint );
}

void controlGraph::mousePressEvent(QMouseEvent * event) {
    emit panPositionRequested(event->x() * visibleRangePan / scene.width() + rangeMinPan);
    emit tiltPositionRequested((scene.height()-event->y()) * visibleRangeTilt / scene.height() + rangeMinTilt);
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
        e->setRect(1.0 * (i->panValue -  rangeMinPan) * scene.width() / visibleRangePan - 15, scene.height() - 1.0 * (i->tiltValue -  rangeMinPan) * scene.height() / visibleRangeTilt - 15 , 30, 30 );
        e->setBrush(QBrush(QColor("#d3f9fe")));
        if(i->timelapseMember == 1)e->setBrush(QBrush(QColor("#19c6ee")));
        e->setZValue(1);

        QGraphicsSimpleTextItem *et = new QGraphicsSimpleTextItem(e);
        et->setPos(1.0 * (i->panValue - rangeMinTilt) * scene.width() / visibleRangePan - 20, scene.height() - 1.0 * (i->tiltValue - rangeMinTilt) * scene.height() / visibleRangeTilt - 30);
        et->setFont(QFont("Calibri", 14, QFont::Normal));

        et->setText(i->name);
        et->setZValue(1);

        elliseFixedPointHash.insert(i.key(), e);
    }
}





