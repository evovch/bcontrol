#ifndef BSOCKET_H
#define BSOCKET_H

#include <QtNetwork/QTcpSocket>

class bSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void sendValue(char prefix, int value);

public slots:
    void reconnect();
    void _onSpeedChanged(int value);
    void _onAngleChanged(int value);
    void _onNewData(void);

};

#endif // BSOCKET_H
