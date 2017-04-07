#include "bgraphicsellipseitem.h"

#include <QDebug>

bGraphicsEllipseItem::bGraphicsEllipseItem( QGraphicsItem * parent ) : QGraphicsEllipseItem(parent)
{
}

void bGraphicsEllipseItem::mousePressEvent(QMouseEvent * event)
{
    qDebug() << "ellipse pressed";
}
