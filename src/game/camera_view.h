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

    byte getColumn(int);
    void setColumn(int, byte);

public:
    CameraView() {};
    void setPosition(Point, bool);
    byte getRow(int pos) { return matrixByte[pos]; }
    void appendColumn(byte);
    void prependColumn(byte);
};

#endif