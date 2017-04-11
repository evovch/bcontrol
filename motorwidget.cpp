#include "motorwidget.h"

#include "ui_motorwidget.h"

motorWidget::motorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::motorWidget)
{
    ui->setupUi(this);

    connect(ui->seekControl, SIGNAL(pressed()), this, SLOT(_onSeekPressed()));
    connect(ui->nullControl, SIGNAL(pressed()), this, SLOT(_onNullPressed()));
    connect(ui->centerControl, SIGNAL(pressed()), this, SLOT(_onCenterPressed()));
    connect(ui->limitControl, SIGNAL(pressed()), this, SLOT(_onLimitPressed()));
    connect(ui->resetControl, SIGNAL(pressed()), this, SLOT(_onResetPressed()));
    connect(ui->powerControl, SIGNAL(pressed()), this, SLOT(_onPowerPressed()));
}

void motorWidget::init(QString ms) {
    motorSuffix = ms;
    ui->nameLabel->setText(motorSuffix);
}

void motorWidget::setPosition(int pos) {
    if(!ui->positionControl->hasFocus())ui->positionControl->setValue(pos);
}

void motorWidget::setPowerControl(bool state) {
    if(state)ui->powerControl->setText("Power: on");
    else ui->powerControl->setText("Power: off");
}

void motorWidget::_onPowerPressed(void) {
   emit doPower(motorSuffix);
}

void motorWidget::_onSeekPressed(void) {
   emit doSeek(motorSuffix, ui->positionControl->value());
}

void motorWidget::_onNullPressed(void) {
   emit doSetNull(motorSuffix);
}

void motorWidget::_onCenterPressed(void) {
   emit doSetCenter(motorSuffix);
}

void motorWidget::_onLimitPressed(void) {
   emit doSetLimit(motorSuffix);
}

void motorWidget::_onResetPressed(void) {
   emit doResetLimit(motorSuffix);
}

motorWidget::~motorWidget()
{
    delete ui;
}
