#include <QtCore/QCoreApplication>
#include <QDebug>
#include "bsocket.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    bSocket *socket = new bSocket();
    socket->reconnect();

    qDebug() << "aaaa";

    return a.exec();
}
