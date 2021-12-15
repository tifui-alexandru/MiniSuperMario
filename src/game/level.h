#ifndef LEVEL_H
#define LEVEL_H
	
#include "camera_view.h"

class Level  {
    static const int noOfColumns = 20;
	int time = 1000; // in seconds
    int id;
    int coinValue = 100;

    byte additionalColumns[noOfColumns] = {
        B00001111,
        B00000001,
        B00000001,
        B00000001,
        B00000000,
        B00000000,
        B00001111,
        B00000001,
        B00000000,
        B00000001,
        B00000001,
        B00000000,
        B00011111,
        B00001111,
        B00000001,
        B00000001,
        B00000000,
        B00000000,
        B00000000,
        B11111111
    };

    byte additionalCoins[noOfColumns] = {
        B00100000,
        B00000000,
        B00100000,
        B00100000,
        B00100000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    struct ErasedCoin {
        Point position;
        ErasedCoin* next;

        ErasedCoin(Point p = Point(0, 0)) : position(p), next(nullptr) {}
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