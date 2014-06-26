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
    if(event->isAutoRepeat())return;
    switch (event->key()) {
    case Qt::Key_A	: {
        qDebug() << "AF pressed";
        emit afChanged(true);
        return;
    }
    case Qt::Key_S	: {
        qDebug() << "SR pressed";
        emit srChanged(true);
        return;
    }
    }

}

void fhead::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A	: {
        qDebug() << "AF released";
        emit afChanged(false);
        return;
    }
    case Qt::Key_S	: {
        qDebug() << "SR released";
        emit srChanged(false);
        return;
    }
    }
}
