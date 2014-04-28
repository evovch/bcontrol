#include "tiltcontrolwidget.h"
#include "ui_tiltcontrolwidget.h"

tiltControlWidget::tiltControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::tiltControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionSlider = ui->positionSlider;
    speedSlider = ui->speedSlider;

    linkUi();
}

tiltControlWidget::~tiltControlWidget()
{
    delete ui;
}
