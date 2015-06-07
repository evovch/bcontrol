#ifndef POLLER_H
#define POLLER_H

#include <QString>
#include <QObject>

class poller : public QObject
{
    Q_OBJECT

private:
    int centerX, centerY, centerZ;
    int rangeX, rangeY, rangeZ;
    int realRangeX = 40;
    int realRangeY = 40;
    int realRangeZ = 40;

    uint maxValue;
    uint maxNormalizedValue;
    bool reverse;

    int lastX = 0, lastY = 0, lastZ = 0;

    const int adcNoiseThreshold = 30;

    int readAdcValue(QString sid);
    int normalizeValue(int val);

public:
   poller(uint mv);

signals:
    void valueChangedX(int value);
    void valueChangedY(int value);
    void valueChangedZ(int value);

public slots:
    void _onPollTimer(void);
};

#endif // POLLER_H
