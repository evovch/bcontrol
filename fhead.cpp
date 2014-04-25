#include "fhead.h"
#include "ui_fhead.h"

fhead::fhead(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fhead)
{
    ui->setupUi(this);
}

fhead::~fhead()
{
    delete ui;
}
