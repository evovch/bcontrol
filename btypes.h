#ifndef BTYPES_H
#define BTYPES_H

typedef struct {
    QString name;
    int panValue;
    int tiltValue;
    int sliderValue;
} fixedPoint;
typedef QHash<QString, fixedPoint> fixedPointHash;

#endif // BTYPES_H
