#ifndef BSOCKET_H
#define BSOCKET_H

#include <QtNetwork/QTcpSocket>
#include <QStringList>

class bSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void send(QString dev, QString key, QString value, QStringList params = QStringList::QStringList());
    void reconnect();

signals:
    void dataReceived(QString dev, QString key, QString value, QStringList arrayValue);
    void bConnected(void);
    void bDisconnected(void);

public slots:
    void _onNewData(void);
    void _onCWatchTimer(void);

};

#endif // BSOCKET_H
