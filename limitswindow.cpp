#include "limitswindow.h"
#include "ui_limitswindow.h"

limitsWindow::limitsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::limitsWindow)
{
    ui->setupUi(this);
}

limitsWindow::~limitsWindow()
{
    delete ui;
}
