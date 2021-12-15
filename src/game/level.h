#ifndef LEVEL_H
#define LEVEL_H
	
#include "camera_view.h"

class Level  {
    static const int noOfColumns = 20;
	int time = 1000; // in seconds
    int id;

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
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    int firstColumnIndex = 0;
    int lastColumnIndex = matrixSize - 1;
    const CameraView initialView;

public:
    Level() {};
    ~Level() {}

    int getTime() { return time; };
    int getId() { return id; };
    int getFirstColumnIndex() { return firstColumnIndex; };
    int getLastColumnIndex() { return lastColumnIndex; };
    const CameraView getInitialView() { return initialView; };

    bool hasNextColumn();
    bool hasPrevColumn();
    byte getNextColumn();
    byte getPrevColumn();
    byte getNextCoinsColumn();
    byte getPrevCoinsColumn();

    bool reachedEndOfTheLevel();

    void restartLevel();

    Level getNewLevel() { return *this; }; // for now  

    Level operator = (const Level& other);
};

#endif