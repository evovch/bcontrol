#include "slidercontrolwidget.h"
#include "ui_slidercontrolwidget.h"

sliderControlWidget::sliderControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::sliderControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionSlider = ui->positionSlider;
    speedSlider = ui->speedSlider;
    positionDial = new QDial();

    linkUi();
}

sliderControlWidget::~sliderControlWidget()
{
    delete ui;
}
