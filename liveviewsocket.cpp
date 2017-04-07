#include "liveviewsocket.h"

#include <QDebug>

void liveViewSocket::reconnect()
{
    connectToHost(hostAddr, 60005);

//    qDebug() << "reconnecting";
    if(waitForConnected(2000)) {
        qDebug() << "LV connected";
        QObject::connect(this, SIGNAL(readyRead()), this, SLOT(_onNewData()));
    }

    qDebug() << "error string: " << errorString();
}

void liveViewSocket::_onCWatchTimer(void) {
    qDebug() << "SSSS: " << state();

    emit stateChanged(state());

    if(state() == QAbstractSocket::UnconnectedState)reconnect();
}

void liveViewSocket::_onNewData(void) {
    mjpegBuffer += readAll();

    QByteArray delim = "--cutjpeg--";

    QByteArray frame;

    int i;
    while(1) {
        i = mjpegBuffer.indexOf(delim);
        if (i==-1) break;

        frame = mjpegBuffer.left(i);
        mjpegBuffer.remove(0, i+delim.size());

        emit gotAFrame(frame);
//        qDebug() << "got a frame: " << i;
    }

//    qDebug() << "bunch done";
}

void liveViewSocket::send()
{
    if(state()==QAbstractSocket::UnconnectedState){
        reconnect();
    }
}

void liveViewSocket::setAddr(QString addr) {
    hostAddr = addr;
}
