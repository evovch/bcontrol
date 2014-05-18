#include "liveview.h"
#include "QDebug"
#include "QLabel"

liveView::liveView(QWidget *parent) :
        QGraphicsView(parent)
{
    QImage img(parent->width(), parent->height(), QImage::Format_RGB32);

    img.load("/Users/korytov/snowww.jpg");


    QLabel lbl;

    lbl.setPixmap(QPixmap::fromImage(img));
    lbl.show();

    qDebug() << "rendering image";

    show();

}
