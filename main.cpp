#include <QtCore>
#include <QtGui>
#include <QSlider>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QObject>
#include "bsocket.h"
#include "ui_fhead.h"
#include "blabel.h"
#include "ui_pancontrolwidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget *mp = new QWidget;
    Ui_fhead ui;
    ui.setupUi(mp);
    mp->show();

    QObject test;

    QObject::connect(ui.panControl->positionSlider, SIGNAL(valueChanged(int)), ui.panControl, SLOT(_onPositionChanged(int)));

    return app.exec();
}
