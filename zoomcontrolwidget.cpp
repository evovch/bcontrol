#include "zoomcontrolwidget.h"
#include "ui_zoomcontrolwidget.h"

zoomControlWidget::zoomControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::zoomControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionDial = ui->positionDial;
    positionSlider = new bSlider();
    speedSlider = ui->speedSlider;

    linkUi();
}

zoomControlWidget::~zoomControlWidget()
{
    delete ui;
}
