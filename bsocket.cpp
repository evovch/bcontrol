#include "bsocket.h"
#include <QDebug>
#include <QRegExp>

void bSocket::reconnect()
{
    connectToHost(hostAddr, 60000);



//    qDebug() << "reconnecting";
    if(waitForConnected(2000)) {
        qDebug() << "connected";
        QObject::connect(this, SIGNAL(readyRead()), this, SLOT(_onNewData()));
    }

    qDebug() << "error string: " << errorString();
}

void bSocket::_onCWatchTimer(void) {
//    qDebug() << state();

    emit stateChanged(state());

    if(state() == QAbstractSocket::UnconnectedState)reconnect();
}

void bSocket::_onNewData(void) {
    QByteArray d = readAll();

    QString str = QString(d);

    QRegExp regexp("([A-Za-z0-9-_]+):([A-Za-z0-9-_]+):([A-Za-za0-9-_/\.]+)?:?([A-Za-za0-9-_,]*)\n");
    int pos = 0;
    while ( (pos = regexp.indexIn(str, pos)) != -1 )
    {
        QStringList params = regexp.cap(4).split( "," );

        emit dataReceived(regexp.cap(1), regexp.cap(2), regexp.cap(3), params);
//        qDebug() << regexp.cap(1) << " --- " << regexp.cap(2) << " --- " << regexp.cap(3);
        pos += regexp.matchedLength();
    }

//    qDebug() << readAll();
}

void bSocket::send(QString dev, QString key, QString value, QStringList params)
{
    if(state()==QAbstractSocket::UnconnectedState){
        reconnect();
    }
    if(state()==QAbstractSocket::ConnectedState){
        QString str = dev + ":" + key + ":" + value + ":" + params.join(",");
        QByteArray byteArray = str.toUtf8();
        const char* cString = byteArray.constData();

        write(cString);
        write("\n");
    }
}

void bSocket::setAddr(QString addr) {
    hostAddr = addr;
}

QString bSocket::getAddr() {
    return hostAddr;
}

