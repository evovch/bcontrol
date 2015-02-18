#ifndef FASTPIXMAPITEM_H
#define FASTPIXMAPITEM_H

#include <QGraphicsItem>
#include <QPainter>

class FastPixmapItem : public QGraphicsItem
{
private:
    QImage currentImage;

public:
    explicit FastPixmapItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPicture(const QImage *i);

signals:
    
public slots:
    
};

#endif // FASTPIXMAPITEM_H
