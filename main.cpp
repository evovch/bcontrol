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
#include "bclient.h"
#include "controlgraph.h"
#include "bcontrolwidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    fhead *mp = new fhead;
    Ui_fhead ui;
    ui.setupUi(mp);
    mp->show();

    bSocket *socket = new bSocket();
    socket->reconnect();

    bClient *cl = new bClient(socket, &ui);

    return app.exec();
}
