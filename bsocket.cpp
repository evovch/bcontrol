#include "bsocket.h"
#include <QDebug>
#include <QRegExp>

void bSocket::reconnect()
{
    connectToHost("95.31.42.166", 60000);
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(_onNewData()));
}

void bSocket::_onNewData(void) {
    QByteArray d = readAll();

    QString str = QString(d);

//    qDebug() << "got:" << str;

    QRegExp regexp("([A-Za-z0-9-_]+):([A-Za-z0-9-_]+):([A-Za-za0-9-_]+)\n");
    int pos = 0;
    while ( (pos = regexp.indexIn(str, pos)) != -1 )
    {
        emit dataReceived(regexp.cap(1), regexp.cap(2), regexp.cap(3));
 //       qDebug() << regexp.cap(1) << " --- " << regexp.cap(2) << " --- " << regexp.cap(3);
        pos += regexp.matchedLength();
    }

//    qDebug() << readAll();
}

void bSocket::send(QString dev, QString key, QString value)
{
    if(state()==QAbstractSocket::ConnectedState){
        QString str = dev + ":" + key + ":" + value ;
        QByteArray byteArray = str.toUtf8();
        const char* cString = byteArray.constData();

        write(cString);
        write("\n");
    }

    if(state()==QAbstractSocket::UnconnectedState){
        reconnect();
    }
}
