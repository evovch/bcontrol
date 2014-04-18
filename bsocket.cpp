#include "bsocket.h"
#include <QDebug>
#include <QRegExp>

void bSocket::reconnect()
{
    connectToHost("95.31.42.166", 60000);
}

void bSocket::_onSpeedChanged(int value) {
    sendValue('s', value);
}

void bSocket::_onAngleChanged(int value) {
    sendValue('a', value);
}

void bSocket::_onNewData(void) {
    QByteArray d = readAll();


    QString str = QString(d);

    QRegExp regexp("done: ([A-Za-z0-9-_]+)\:([A-Za-za0-9-_]+)\r");
    int pos = 0;
    while ( (pos = regexp.indexIn(str, pos)) != -1 )
    {
        qDebug() << regexp.cap(1) << " --- " << regexp.cap(2);
        pos += regexp.matchedLength();
    }

//    qDebug() << readAll();
}

void bSocket::sendValue(char prefix, int value)
{
    char str[20];
    sprintf(str, "%d", value);

    if(state()==QAbstractSocket::ConnectedState){
        write(&prefix, 1);
        write(":");
        write(str);
        write("\r");
    }

    if(state()==QAbstractSocket::UnconnectedState){
        reconnect();
    }
}
