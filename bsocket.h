#ifndef BSOCKET_H
#define BSOCKET_H

#include <QTcpSocket>
#include <QStringList>

class bSocket : public QTcpSocket
{
    Q_OBJECT

public:
    void send(QString dev, QString key, QString value, QStringList params = QStringList());
    void reconnect(void);
    void setAddr(QString addr);
    QString getAddr(void);

signals:
    void dataReceived(QString dev, QString key, QString value, QStringList arrayValue);
    void bConnected(void);
    void bDisconnected(void);
    void bReconnecting(void);

public slots:
    void _onNewData(void);
    void _onCWatchTimer(void);

private:
    QString hostAddr = "127.0.0.1";
//    QString hostAddr = "172.16.248.200";

};

#endif // BSOCKET_H
