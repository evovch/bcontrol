#include <QApplication>

/*#include <QtCore>
#include <QtGui>
#include <QStatusBar>
#include <QMainWindow>
#include <QSizePolicy>
#include <QSlider>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QObject>*/

#include "bclient.h"

/*#include "bsocket.h"
#include "ui_fhead.h"
#include "blabel.h"
#include "controlgraph.h"
#include "bcontrolwidget.h"
#include "ui_bmotion.h"
#include "bmotion.h"*/

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    bClient *cl = new bClient();

    return app.exec();
}
