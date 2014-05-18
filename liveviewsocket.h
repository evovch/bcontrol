#ifndef LIVEVIEWSOCKET_H
#define LIVEVIEWSOCKET_H

#include <QTcpSocket>

class liveViewSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void send();
    void reconnect();

private:
    QByteArray mjpegBuffer;

signals:
    void gotAFrame(QByteArray frame);

public slots:
    void _onNewData(void);
};

#endif // LIVEVIEWSOCKET_H
