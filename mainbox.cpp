#include "mainbox.h"
#include "ui_mainbox.h"

mainBox::mainBox(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint),
    ui(new Ui::mainBox)
{
    ui->setupUi(this);
}

mainBox::~mainBox()
{
    delete ui;
}
