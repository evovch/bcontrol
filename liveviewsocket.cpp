#include "liveviewsocket.h"
#include <QDebug>


void liveViewSocket::reconnect()
{
    connectToHost("95.31.42.166", 60005);
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(_onNewData()));
}

void liveViewSocket::_onNewData(void) {
    mjpegBuffer += readAll();

    QByteArray delim = "--cutjpeg--";

    QByteArray frame;

    int i;
    while(1) {
        i = mjpegBuffer.indexOf(delim);
        if(i==-1)break;

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
