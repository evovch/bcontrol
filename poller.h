#ifndef POLLER_H
#define POLLER_H

#include <QString>
#include <QObject>

class poller : public QObject
{
    Q_OBJECT

private:
    int minX = 200;
    int maxX = 4000;
    int centerX = 2100;
    int realRangeX = 200;

    int minY = 200;
    int maxY = 4000;
    int centerY = 2100;
    int realRangeY = 200;

    int minZ = 200;
    int maxZ = 4000;
    int centerZ = 2100;
    int realRangeZ = 200;

    int lastX = 0, lastY = 0, lastZ = 0;

    const int adcNoiseThreshold = 10;

    int readAdcValue(QString sid);

public:
    poller();

signals:
    void valueChangedX(int value);
    void valueChangedY(int value);
    void valueChangedZ(int value);

public slots:
    void _onPollTimer(void);
};

#endif // POLLER_H
