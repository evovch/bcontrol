#include "fhead.h"

#include "ui_fhead.h"

#include <QDebug>
#include <QKeyEvent>

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
        case Qt::Key_W	: {
            qDebug() << "ZoomIn pressed";
            emit zoomInChanged(true);
            return;
        }
        case Qt::Key_Q	: {
            qDebug() << "ZoomOut pressed";
            emit zoomOutChanged(true);
            return;
        }
        case Qt::Key_K	: {
            emit fpPressed();
            return;
        }
        case Qt::Key_Z	: {
            emit afAndCaptureKey();
            return;
        }
    }
}

void fhead::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A	: {
            emit afChanged(false);
            return;
        }
        case Qt::Key_S	: {
            emit srChanged(false);
            return;
        }
        case Qt::Key_W	: {
            emit zoomInChanged(false);
            return;
        }
        case Qt::Key_Q	: {
            emit zoomOutChanged(false);
            return;
        }
    }
}
