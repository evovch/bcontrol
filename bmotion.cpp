#include "bmotion.h"

#include <QMouseEvent>
#include <QDebug>

#include "ui_bmotion.h"

bmotion::bmotion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bmotion)
{
    ui->setupUi(this);
    setMouseTracking(false);
    trackingOn = false;
}

bmotion::~bmotion() {
    delete ui;
}

void bmotion::mouseMoveEvent (QMouseEvent *event) {
    qDebug() << "mouse event received";

    if(trackingOn) {
        emit virtualX(( (double)event->x() / this->width() ) * 10000);
        emit virtualY(( (double)event->y() / this->height() ) * 10000);
    }
}

void bmotion::mousePressEvent (QMouseEvent *event) {
    if(trackingOn) {
        setStyleSheet("background-color:none;");
        setMouseTracking(false);
        trackingOn = false;
        emit virtualX(5000);
        emit virtualY(5000);
    } else {
        setStyleSheet("background-color:#b7d6ee;");
        setMouseTracking(true);
        trackingOn = true;
    }
}
