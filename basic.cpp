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
#include "ui_main.h"
#include "blabel.h"

int main_basic(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QGridLayout *mainLayout = new QGridLayout;

    QWidget *mp = new QWidget;
    Ui_mainPanel ui;
    ui.setupUi(mp);
    mp->show();

    bSocket *socket = new bSocket();
    socket->reconnect();

    QObject::connect(ui.angleSlider, SIGNAL(valueChanged(int)), socket, SLOT(_onAngleChanged(int)));
    QObject::connect(ui.speedSlider, SIGNAL(valueChanged(int)), socket, SLOT(_onSpeedChanged(int)));
    QObject::connect(ui.speedSlider, SIGNAL(sliderReleased()), ui.speedSlider, SLOT(reset()));
    QObject::connect(socket, SIGNAL(readyRead()), socket, SLOT(_onNewData()));
    QObject::connect(socket, SIGNAL(dataReceived(QString, QString)), ui.lPosition, SLOT(_onDataReceived(QString, QString)));

    return app.exec();
}
