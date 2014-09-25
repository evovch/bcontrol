#include "focuscontrolwidget.h"
#include "ui_focuscontrolwidget.h"

focusControlWidget::focusControlWidget(QWidget *parent) :
    motorControlWidget(parent),
    ui(new Ui::focusControlWidget)
{
    ui->setupUi(this);

    coordLabel = ui->coordLabel;
    positionSlider = ui->positionSlider;
    speedSlider = new bSlider(); //empty for compatibility

    linkUi();
}

focusControlWidget::~focusControlWidget()
{
    delete ui;
}
