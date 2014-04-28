#include "pancontrolwidget.h"
#include "ui_pancontrolwidget.h"

panControlWidget::panControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::panControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionSlider = ui->positionSlider;
    speedSlider = ui->speedSlider;

    linkUi();
}

panControlWidget::~panControlWidget()
{
    delete ui;
}
