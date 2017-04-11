#ifndef FOCUSPOINT_H
#define FOCUSPOINT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>

class focusPoint : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    focusPoint(unsigned int cid, int x, int y, QGraphicsItem *parent = 0);

    const int fullWidth = 4928;
    const int fullHeight = 3280;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    
signals:
    void focusPointPressed(int);
    
public slots:

private:
    unsigned int id;

};

#endif // FOCUSPOINT_H
