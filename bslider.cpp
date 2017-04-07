#include "bslider.h"

bSlider::bSlider(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent) {
}

bSlider::bSlider(QWidget *parent) : QSlider(parent) {
}

void bSlider::reset(void)
{
    setValue(0);
}
