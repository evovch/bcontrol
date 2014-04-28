#include "motorcontrolwidget.h"

motorControlWidget::motorControlWidget(QWidget *parent) :
    QWidget(parent)
{
}

void motorControlWidget::linkUi(void)
{
    positionSlider->setFocusPolicy(Qt::StrongFocus);
    speedSlider->setFocusPolicy(Qt::StrongFocus);
    QObject::connect(speedSlider, SIGNAL(sliderReleased()), speedSlider, SLOT(reset()));
    QObject::connect(positionSlider, SIGNAL(valueChanged(int)), this, SLOT(_onPositionSliderValueChanged(int)));
    QObject::connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(_onSpeedSliderValueChanged(int)));
}

void motorControlWidget::_onPositionChanged(int value){
    setPosition(value);
}

void motorControlWidget::_onPositionSliderValueChanged(int value){
    if(positionSlider->hasFocus())emit positionChanged(value);
}

void motorControlWidget::_onSpeedSliderValueChanged(int value){
    emit speedChanged(value);
}

void motorControlWidget::setPosition(int value){
    coordLabel->setText(QString::number(value));
    if(!positionSlider->hasFocus())positionSlider->setValue(value);
}
