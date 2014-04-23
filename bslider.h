#ifndef BSLIDER_H
#define BSLIDER_H

#include <QSlider>

class bSlider : public QSlider
{
    Q_OBJECT

public:
    bSlider(Qt::Orientation orientation, QWidget *parent = 0);
    bSlider(QWidget *parent = 0);

public slots:
    void reset();
};

#endif // BSLIDER_H
