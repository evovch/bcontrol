#include <QtCore/QCoreApplication>
#include <QDebug>
#include "bsocket.h"
#include "poller.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    bSocket *socket = new bSocket();
    socket->reconnect();

    qDebug() << "strarting up bJoy";

    poller p = new poller();

    return a.exec();
}
