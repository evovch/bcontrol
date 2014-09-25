#include "zoomcontrolwidget.h"
#include "ui_zoomcontrolwidget.h"

zoomControlWidget::zoomControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::zoomControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionSlider = ui->positionSlider;
    speedSlider = new bSlider(); //empty for compatibility

    linkUi();
}

zoomControlWidget::~zoomControlWidget()
{
    delete ui;
}
