#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

#include "../../include/utils.h"
	
class CameraView {
    /*
        There is impossible to have a Point(x, y)
        where mapMatrix[x][y] and coninsMatrix[x][y] 
        are both set true
    */

	byte mapMatrix[matrixSize] = {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000100,
        B00000100,
        B11111111
    };

    byte coinsMatrix[matrixSize] = {
        B00000000,
        B00000000,
        B00000000,
        B00000100,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    byte getColumn(byte*, int);

public:
    CameraView() {};
    CameraView(const CameraView&);
    CameraView operator = (const CameraView&);

    byte getMapColumn(int pos) { return getColumn(mapMatrix, pos); }
    byte getCoinsColumn(int pos) { return getColumn(coinsMatrix, pos); }

    byte getMapRow(int pos) { return mapMatrix[pos]; }
    byte getCoinsRow(int pos) { return coinsMatrix[pos]; }

    void setPosition(Point, bool);
    void setColumn(byte*, int, byte);

    void appendColumn(byte, byte);
    void prependColumn(byte, byte);

    void changeCoinsState(bool);

    bool isObstacle(Point);
    bool isCoin(Point);

    void eraseCoin(Point);
};

#endif