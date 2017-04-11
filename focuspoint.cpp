#include "focuspoint.h"

#include <QPen>
#include <QDebug>

focusPoint::focusPoint(unsigned int cid, int x, int y, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    id = cid;

    float xRate = this->parentItem()->boundingRect().width() / fullWidth;
    float yRate = this->parentItem()->boundingRect().height() / fullHeight;
    setRect(x * xRate, y * yRate, 135 * xRate, 135 * yRate);
    setPen(QPen(QColor("white")));
    setZValue(2);
}

void focusPoint::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    qDebug() << "focus point pressed: " << id;
    emit(focusPointPressed(id));
}
