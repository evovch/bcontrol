#include "motorcontrolwidget.h"

motorControlWidget::motorControlWidget(QWidget *parent) :
    QWidget(parent)
{
}

void motorControlWidget::linkUi(void)
{
    QObject::connect(speedSlider, SIGNAL(sliderReleased()), speedSlider, SLOT(reset()));
}

void motorControlWidget::_onPositionChanged(int value){
    positionBar->setValue(value);
    coordLabel->setText(QString::number(value));
}
