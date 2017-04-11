#ifndef FASTPIXMAPITEM_H
#define FASTPIXMAPITEM_H

#include <QGraphicsItem>
#include <QImage>

class FastPixmapItem : public QGraphicsItem
{

public:
    explicit FastPixmapItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPicture(const QImage *i);

signals:
    
public slots:
    
private:
    QImage currentImage;

};

#endif // FASTPIXMAPITEM_H
