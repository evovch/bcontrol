#include "bslider.h"

bSlider::bSlider(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent) {}

void bSlider::reset()
{
    setValue(0);
}

