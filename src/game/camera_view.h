#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

#include "../../include/utils.h"
	
class CameraView {
	byte matrixByte[matrixSize] = {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B11111111
    };

public:
    CameraView() {};
    CameraView operator = (const CameraView&);

    byte getRow(int pos) { return matrixByte[pos]; }
    byte getColumn(int);

    void setPosition(Point, bool);
    void setColumn(int, byte);

    void appendColumn(byte);
    void prependColumn(byte);

    bool hasObstacle(Point);
};

#endif