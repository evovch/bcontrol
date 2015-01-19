#ifndef POLLER_H
#define POLLER_H

#include <QString>
#include <QObject>

class poller : public QObject
{
    Q_OBJECT

private:
    int readAdcValue(QString sid);

public:
    poller();

public slots:
    void _onPollTimer(void);
};

#endif // POLLER_H
