#ifndef POLLER_H
#define POLLER_H

#include <QString>
#include <QObject>

class poller : public QObject
{
    Q_OBJECT

private:
    const int minX = 200;
    const int maxX = 4000;
    const int centerX = 2100;
    const int realRangeX = 100;

    const int minY = 200;
    const int maxY = 4000;
    const int centerY = 2100;
    const int realRangeY = 100;

    const int minZ = 200;
    const int maxZ = 4000;
    const int centerZ = 2100;
    const int realRangeZ = 100;

    int lastX = 0, lastY = 0, lastZ = 0;

    const int adcNoiseThreshold = 10;

    int readAdcValue(QString sid);

public:
    poller();

public slots:
    void _onPollTimer(void);
};

#endif // POLLER_H
