#ifndef MOTORCONTROLWIDGET_H
#define MOTORCONTROLWIDGET_H

#include <QWidget>
#include "bslider.h"
#include <QtGui>

class motorControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit motorControlWidget(QWidget *parent = 0);
    void linkUi(void);

    QLabel *coordLabel;
    QSlider *positionSlider;
    bSlider *speedSlider;
    QProgressBar *positionBar;

signals:
    void newSpeed(int value);
    void newPosition(int value);

public slots:
    void _onPositionChanged(int value);
    
};

#endif // MOTORCONTROLWIDGET_H
