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
#include <QStatusBar>
#include <QMainWindow>
#include <QSizePolicy>
#include "ui_bmotion.h"
#include "bmotion.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    bClient *cl = new bClient();

    return app.exec();
}
