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

typedef struct {
    int rangeMinPan;
    int rangeMaxPan;
    int rangeMinTilt;
    int rangeMaxTilt;
    int rangeMinFocus;
    int rangeMaxFocus;
    int rangeMinZoom;
    int rangeMaxZoom;
    int rangeMinSlider;
    int rangeMaxSlider;

    int powerStatusPan;
    int powerStatusTilt;
    int powerStatusFocus;
    int powerStatusZoom;
    int powerStatusSlider;

    int reverseDirPan;
    int reverseDirTilt;
    int reverseDirFocus;
    int reverseDirZoom;
    int reverseDirSlider;

} motorsInfo;

#endif // BTYPES_H
