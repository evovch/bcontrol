#include "fastpixmapitem.h"

#include <QDebug>

FastPixmapItem::FastPixmapItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    currentImage = QImage();
}

QRectF FastPixmapItem::boundingRect() const {
    return QRectF(0, 0, currentImage.width(), currentImage.height());
}

void FastPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//         painter->setBrush(currentBrush);
//         painter->drawRoundedRect(10, 10, 20, 20, 5, 5);
         painter->drawImage(QPoint(0,0), currentImage);
//         qDebug() << "painting";

}

void FastPixmapItem::setPicture(const QImage *i) {
    currentImage = *i;
    update();
}
