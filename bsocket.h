#ifndef BSOCKET_H
#define BSOCKET_H

#include <QtNetwork/QTcpSocket>
#include <QStringList>

class bSocket : public QTcpSocket
{
    Q_OBJECT

private:
    QString hostAddr = "192.168.1.100";
//    QString hostAddr = "172.16.248.200";

public:
    void send(QString dev, QString key, QString value, QStringList params = QStringList()); // TODO how is that?
    void reconnect();
    void setAddr(QString addr);
    QString getAddr();

signals:
    void dataReceived(QString dev, QString key, QString value, QStringList arrayValue);
    void bConnected(void);
    void bDisconnected(void);
    void bReconnecting(void);

public slots:
    void _onNewData(void);
    void _onCWatchTimer(void);

};

#endif // BSOCKET_H
