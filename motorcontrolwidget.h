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
    bSlider *positionSlider;
    bSlider *speedSlider;
    QProgressBar *positionBar;

    void setPosition(int value);

signals:
//    void newSpeed(int value);
    void positionChanged(int value);
    void speedChanged(int value);

public slots:
    void _onPositionChanged(int value);
    void _onPositionSliderValueChanged(int value);
    void _onSpeedSliderValueChanged(int value);
};

#endif // MOTORCONTROLWIDGET_H