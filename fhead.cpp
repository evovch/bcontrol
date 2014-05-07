#include "fhead.h"
#include "ui_fhead.h"
#include <QDebug>

fhead::fhead(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fhead)
{
     qDebug() << "constructing fhead";
}

fhead::~fhead()
{
}

void fhead::keyPressEvent(QKeyEvent *event)
{
         qDebug() << "key pressed";
    if(event->key() == Qt::Key_Escape)
    {
        qDebug() << "esc pressed";
//        myLabel->setText("You pressed ESC");
    }
}

void fhead::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
//        myLabel->setText("You released ESC");
    }
}
