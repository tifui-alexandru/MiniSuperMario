#ifndef LEVEL_H
#define LEVEL_H
	
#include "camera_view.h"

class Level  {
    static const int noOfColumns = 5;
	int time = 1000; // in seconds
    int id;
    int coinValue = 100;

    byte additionalColumns[noOfColumns] = {
        wallType[0],
        hole,
        hole,
        hole,
        endWall
    };

    byte additionalCoins[noOfColumns] = {
        noCoin,
        coinCol4,
        noCoin,
        coinCol4,
        noCoin
    };

    struct ErasedCoin {
        Point panCameraPos;
        Point realPos;
        ErasedCoin* next;

        ErasedCoin(Point p1 = Point(0, 0), Point p2 = Point(0, 0)) : panCameraPos(p1), realPos(p2), next(nullptr) {}
    };
    ErasedCoin* headErasedCoin = nullptr;

    int firstColumnIndex = 0;
    int lastColumnIndex = matrixSize - 1;
    CameraView initialView;

public:
    Level() {};
    ~Level() {}

    int getTime() { return time; };
    int getId() { return id; };
    int getCoinValue() { return coinValue; };
    int getFirstColumnIndex() { return firstColumnIndex; };
    int getLastColumnIndex() { return lastColumnIndex; };
    const CameraView getInitialView() { return initialView; };

    bool hasNextColumn();
    bool hasPrevColumn();

    byte getNextColumn();
    byte getPrevColumn();

    byte getNextCoinsColumn();
    byte getPrevCoinsColumn();
    
    void moveCameraRight();
    void moveCameraLeft();

    bool reachedEndOfTheLevel();

    void restartLevel();

    void eraseCoin(Point);

    Level getNewLevel() { return *this; }; // for now  

    Level operator = (const Level& other);
};

#endif