#include "timelapse.h"
#include "ui_timelapse.h"

timelapse::timelapse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timelapse)
{
    ui->setupUi(this);
}

timelapse::~timelapse()
{
    delete ui;
}
