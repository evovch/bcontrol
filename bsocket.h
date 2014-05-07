#ifndef BSOCKET_H
#define BSOCKET_H

#include <QtNetwork/QTcpSocket>
#include <QStringList>

class bSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void send(QString dev, QString key, QString value);

signals:
    void dataReceived(QString dev, QString key, QString value, QStringList arrayValue);

public slots:
    void reconnect();
    void _onNewData(void);

};

#endif // BSOCKET_H
