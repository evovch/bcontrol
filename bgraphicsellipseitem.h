#ifndef BGRAPHICSELLIPSEITEM_H
#define BGRAPHICSELLIPSEITEM_H

#include <QGraphicsEllipseItem>

class QMouseEvent;

class bGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    bGraphicsEllipseItem(QGraphicsItem* parent = 0);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // BGRAPHICSELLIPSEITEM_H
