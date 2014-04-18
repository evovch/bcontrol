#include <QtCore>
#include <QtGui>
#include <QSlider>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QObject>
#include "bsocket.h"
#include "bslider.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    QBoxLayout *angleLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *speedLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QDialog *dialog = new QDialog;

    QSlider *angleSlider;
    angleSlider = new QSlider(Qt::Horizontal);
    angleSlider->setFocusPolicy(Qt::StrongFocus);
    angleSlider->setTickPosition(QSlider::TicksBothSides);
    angleSlider->setTickInterval(10);
    angleSlider->setSingleStep(1);
    angleSlider->setFixedWidth(200);
    angleSlider->setMinimum(-100);
    angleSlider->setMaximum(100);
    angleSlider->setSliderPosition(0);

    bSlider *speedSlider;
    speedSlider = new bSlider(Qt::Horizontal);
    speedSlider->setFocusPolicy(Qt::StrongFocus);
    speedSlider->setTickPosition(QSlider::TicksBothSides);
    speedSlider->setTickInterval(10);
    speedSlider->setSingleStep(1);
    speedSlider->setFixedWidth(200);
    speedSlider->setMinimum(-100);
    speedSlider->setMaximum(100);
    speedSlider->setSliderPosition(0);

    angleLayout->addWidget(new QLabel("Angle"), Qt::AlignLeft);
    angleLayout->addWidget(angleSlider, Qt::AlignLeft);

    speedLayout->addWidget(new QLabel("Speed"), Qt::AlignLeft);
    speedLayout->addWidget(speedSlider, Qt::AlignLeft);

    mainLayout->addLayout(angleLayout);
    mainLayout->addLayout(speedLayout);

    dialog->setLayout(mainLayout);
    dialog->show();


    bSocket *socket = new bSocket();
    socket->reconnect();

    QObject::connect(angleSlider, SIGNAL(valueChanged(int)), socket, SLOT(_onAngleChanged(int)));
    QObject::connect(speedSlider, SIGNAL(valueChanged(int)), socket, SLOT(_onSpeedChanged(int)));
    QObject::connect(speedSlider, SIGNAL(sliderReleased()), speedSlider, SLOT(reset()));
    QObject::connect(socket, SIGNAL(readyRead()), socket, SLOT(_onNewData()));

    return app.exec();
}
