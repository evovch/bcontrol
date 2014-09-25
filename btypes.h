#ifndef BTYPES_H
#define BTYPES_H

typedef struct {
    QString name;
    int panValue;
    int tiltValue;
    int zoomValue;
    int focusValue;
    int sliderValue;

    int timelapseMember;
} fixedPoint;
typedef QHash<QString, fixedPoint> fixedPointHash;
typedef QVector<fixedPoint> fixedPointArray;

#endif // BTYPES_H
