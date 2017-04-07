#include "controlgraph.h"

#include <QDebug>
#include <QThread>

#include <turbojpeg.h>

#include "bgraphicsellipseitem.h"

controlGraph::controlGraph(QWidget *parent) :
    QGraphicsView(parent)
{
    setRange(0, 0, 100, 100);

    setInteractive(true);

    setGeometry(0, 0, parent->width(), parent->height());

    scene.setSceneRect( 0.0, 0.0, this->width()-4, this->height()-4 );
    setScene(&scene);

    lineTilt = new QGraphicsLineItem(0);
    scene.addItem(lineTilt);
//    lineTilt->setLine(0, 100.0, scene.width(), 100.0 );
    lineTilt->setZValue(2);

    linePan = new QGraphicsLineItem(0);
    scene.addItem(linePan);
//    linePan->setLine(100.0, 0, 100.0, scene.height() );
    linePan->setZValue(2);

//    QGraphicsView( &scene, parent );
//    setRenderHints( QPainter::Antialiasing );
    show();

    sceneLV.setSceneRect( 0.0, 0.0, this->width()-4, this->height()-4 );
    fpPlot = new QGraphicsRectItem(0, 0, sceneLV.width(), sceneLV.height());
    fpPlot->setZValue(1);
    sceneLV.addItem(fpPlot);

//    QImage img(parent->width(), parent->height(), QImage::Format_RGB32);
//    img.load("/home/korytov/bbin/pics/1/correct.jpg");
//    img.load("/Users/korytov/2/correct.jpg");


//    QFile f("/Users/korytov/2/correct2.jpg");
//    f.open(QIODevice::ReadOnly);

    currentFrameBuffer = (unsigned char*)malloc(1);
    framerBusy = false;

  //  _onGotAFrame(f.readAll());

 //   QPixmap pm = QPixmap::fromImage(img);
 //   pm = pm.scaled(sceneLV.width(), sceneLV.height(),  Qt::KeepAspectRatio, Qt::SmoothTransformation);

//    lvSnapshot.setPixmap(pm);
    sceneLV.addItem(&lvSnapshot);

 //   scene.addItem(&lvSnapshot);

    lvSnapshot.setZValue(0);
    createFocusPoints();

    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

//    setLVScene();

    activeFocusPointIndex = 1000;
}

void controlGraph::hightlightFocusPoint(int index) {
    if(activeFocusPointIndex == index)return;
    if(activeFocusPointIndex != 1000)focusPoints.at(activeFocusPointIndex)->setPen(QPen(QColor("#ffffff")));
    focusPoints.at(index)->setPen(QPen(QColor("#fc5c61")));
    activeFocusPointIndex = index;
}

void controlGraph::createFocusPoints() {
    focusPoints.append(new focusPoint(0, 2487, 1665, fpPlot));
    focusPoints.append(new focusPoint(1, 2487, 1408, fpPlot));
    focusPoints.append(new focusPoint(2, 2487, 1152, fpPlot));
    focusPoints.append(new focusPoint(3, 2487, 1921, fpPlot));
    focusPoints.append(new focusPoint(4, 2487, 2177, fpPlot));
    focusPoints.append(new focusPoint(5, 2743, 1665, fpPlot));
    focusPoints.append(new focusPoint(6, 2743, 1408, fpPlot));
    focusPoints.append(new focusPoint(7, 2743, 1152, fpPlot));
    focusPoints.append(new focusPoint(8, 2743, 1921, fpPlot));
    focusPoints.append(new focusPoint(9, 2743, 2177, fpPlot));
    focusPoints.append(new focusPoint(10, 2230, 1665, fpPlot));
    focusPoints.append(new focusPoint(11, 2230, 1408, fpPlot));
    focusPoints.append(new focusPoint(12, 2230, 1152, fpPlot));
    focusPoints.append(new focusPoint(13, 2230, 1921, fpPlot));
    focusPoints.append(new focusPoint(14, 2230, 2177, fpPlot));
    focusPoints.append(new focusPoint(15, 2995, 1665, fpPlot));
    focusPoints.append(new focusPoint(16, 2995, 1472, fpPlot));
    focusPoints.append(new focusPoint(17, 2995, 1280, fpPlot));
    focusPoints.append(new focusPoint(18, 2995, 1856, fpPlot));
    focusPoints.append(new focusPoint(19, 2995, 2048, fpPlot));
    focusPoints.append(new focusPoint(20, 3250, 1665, fpPlot));
    focusPoints.append(new focusPoint(21, 3250, 1472, fpPlot));
    focusPoints.append(new focusPoint(22, 3250, 1280, fpPlot));
    focusPoints.append(new focusPoint(23, 3250, 1856, fpPlot));
    focusPoints.append(new focusPoint(24, 3250, 2048, fpPlot));
    focusPoints.append(new focusPoint(25, 3505, 1665, fpPlot));
    focusPoints.append(new focusPoint(26, 3505, 1472, fpPlot));
    focusPoints.append(new focusPoint(27, 3505, 1280, fpPlot));
    focusPoints.append(new focusPoint(28, 3505, 1856, fpPlot));
    focusPoints.append(new focusPoint(29, 3505, 2048, fpPlot));
    focusPoints.append(new focusPoint(30, 3760, 1665, fpPlot));
    focusPoints.append(new focusPoint(31, 3760, 1472, fpPlot));
    focusPoints.append(new focusPoint(32, 3760, 1856, fpPlot));
    focusPoints.append(new focusPoint(33, 1975, 1665, fpPlot));
    focusPoints.append(new focusPoint(34, 1975, 1472, fpPlot));
    focusPoints.append(new focusPoint(35, 1975, 1280, fpPlot));
    focusPoints.append(new focusPoint(36, 1975, 1856, fpPlot));
    focusPoints.append(new focusPoint(37, 1975, 2048, fpPlot));
    focusPoints.append(new focusPoint(38, 1720, 1665, fpPlot));
    focusPoints.append(new focusPoint(39, 1720, 1472, fpPlot));
    focusPoints.append(new focusPoint(40, 1720, 1280, fpPlot));
    focusPoints.append(new focusPoint(41, 1720, 1856, fpPlot));
    focusPoints.append(new focusPoint(42, 1720, 2048, fpPlot));
    focusPoints.append(new focusPoint(43, 1465, 1665, fpPlot));
    focusPoints.append(new focusPoint(44, 1465, 1472, fpPlot));
    focusPoints.append(new focusPoint(45, 1465, 1280, fpPlot));
    focusPoints.append(new focusPoint(46, 1465, 1856, fpPlot));
    focusPoints.append(new focusPoint(47, 1465, 2048, fpPlot));
    focusPoints.append(new focusPoint(48, 1210, 1665, fpPlot));
    focusPoints.append(new focusPoint(49, 1210, 1472, fpPlot));
    focusPoints.append(new focusPoint(50, 1210, 1856, fpPlot));
}

QList<focusPoint *> controlGraph::getFocusPoints(void) {
    return focusPoints;
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
        if(touchEvent->touchPoints().size() < 2) {
//            emit touchMove(0, 0);
            return(true);
        }
        qDebug() << "touch TouchUpdate";
        const QTouchEvent::TouchPoint &touchPoint0 = touchEvent->touchPoints().first();

        int s = 1;
        if(touchEvent->touchPoints().size() == 3)s = 10;

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
    case QEvent::TouchCancel:
    {
        emit touchMove(0, 0);

        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void controlGraph::setLVScene(Mode m) {
    if (currentScene == &sceneLV)return;
    currentScene = &sceneLV;
    setScene(&sceneLV);

    if(m == MODE_VIEWFINDER_CAM) {
        lvSnapshot.setZValue(3);
    }
    else {
        lvSnapshot.setZValue(0);
    }
}

void controlGraph::setFPScene() {
    if (currentScene == &scene)return;
    currentScene = &scene;
    setScene(&scene);
}

void controlGraph::_onGotAFrame(QByteArray frame) {
    if(framerBusy) {
        qDebug() << "frame skipped - busy!";
    }
    framerBusy = true;

//    qDebug() << "got new frame: " << frame.size();

    long unsigned int _jpegSize = frame.size(); //!< _jpegSize from above
    unsigned char* _compressedImage = (unsigned char*)frame.data(); //!< _compressedImage from above

    int jpegSubsamp, width, height;

    tjhandle _jpegDecompressor = tjInitDecompress();

    tjDecompressHeader2(_jpegDecompressor, _compressedImage, _jpegSize, &width, &height, &jpegSubsamp);
//    qDebug() << "size: " << width << "x" << height;
//    qDebug() << "subsamp: " << jpegSubsamp;
    if(jpegSubsamp < 0 || (width != 640 && width != 960)) {
        qDebug() << "corrupted frame";
        tjDestroy(_jpegDecompressor);
        framerBusy = false;
        return;
     }

//    int targetWidth = this->width();
//    int targetHeight = height * (float)targetWidth / width;

//    qDebug() << "target size: " << targetWidth << "x" << targetHeight;

    free(currentFrameBuffer);
    currentFrameBuffer = (unsigned char*)malloc(width*height*tjPixelSize[TJPF_RGB]);

    int res = tjDecompress2(_jpegDecompressor, _compressedImage, _jpegSize, currentFrameBuffer, width,  0 /*pitch*/, height, TJPF_RGB, TJFLAG_FASTDCT);
//    qDebug() << "tjDecompress2: " << res;

    tjDestroy(_jpegDecompressor);
  QImage i(currentFrameBuffer, width, height, QImage::Format_RGB888);
//   QImage i();
//    i.save("/Users/korytov/2/_out.jpg", "JPEG");

    if(i.width() != this->width()) {
//        qDebug() << "scaling to viewport: " << i.width() << " -> " << this->width();
        i = i.scaled(this->width(), this->height());
    }

   QPixmap pm = QPixmap::fromImage(i);
//   lvSnapshot.setTransformationMode(Qt::FastTransformation);
    lvSnapshot.setPixmap(pm);

//    lvSnapshot.setPicture(&i);

    framerBusy = false;
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
    if(visibleRangePan == 0)return;

    int linePoint = (qreal) (value -  rangeMinPan) * (qreal)scene.width() / visibleRangePan;
    linePan->setLine(linePoint, 0, linePoint, scene.height() );
}

void controlGraph::setTiltPosition(int value){
    if(visibleRangeTilt == 0)return;

    int linePoint = (qreal) (value - rangeMinTilt) * (qreal)scene.height() / visibleRangeTilt;
    lineTilt->setLine(0, scene.height()-linePoint, scene.width(), scene.height()-linePoint );
}


void controlGraph::mousePressEvent(QMouseEvent * event) {
    if(currentScene == &scene) {
        emit panPositionRequested(event->x() * visibleRangePan / scene.width() + rangeMinPan);
        emit tiltPositionRequested((scene.height()-event->y()) * visibleRangeTilt / scene.height() + rangeMinTilt);
    }

    QGraphicsView::mousePressEvent(event);
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





