#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

#include "../../include/utils.h"
#include "game_utils.h"
	
class CameraView {
    /*
        There is impossible to have a Point(x, y)
        where mapMatrix[x][y] and coninsMatrix[x][y] 
        are both set true
    */

    byte mapColumns[matrixSize] = {
        gameFloor,
        gameFloor,
        gameFloor,
        gameFloor,
        gameFloor,
        wallHeight2,
        gameFloor,
        gameFloor
    };

    byte coinsColumns[matrixSize] = {
        noCoin,
        noCoin,
        noCoin,
        noCoin,
        noCoin,
        coinCol4,
        noCoin,
        noCoin
    };

    byte mapMatrix[matrixSize];
    byte coinsMatrix[matrixSize];

    byte getColumn(byte*, int);

public:
    CameraView();
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
    void setCoin(Point);
};

#endif