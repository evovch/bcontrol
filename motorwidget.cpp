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
}

void motorWidget::init(QString ms) {
    motorSuffix = ms;
    ui->nameLabel->setText(motorSuffix);
}

void motorWidget::setPosition(int pos) {
    if(!ui->positionControl->hasFocus())ui->positionControl->setValue(pos);
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
