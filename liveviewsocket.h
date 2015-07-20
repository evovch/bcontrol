#ifndef LIVEVIEWSOCKET_H
#define LIVEVIEWSOCKET_H

#include <QTcpSocket>

class liveViewSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void send();
    void reconnect();
    void setAddr(QString addr);

private:
    QByteArray mjpegBuffer;
    QString hostAddr = "172.16.248.200";

signals:
    void gotAFrame(QByteArray frame);
    void bConnected(void);
    void bDisconnected(void);

public slots:
    void _onNewData(void);
    void _onCWatchTimer(void);
};

#endif // LIVEVIEWSOCKET_H
