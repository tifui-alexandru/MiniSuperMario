#ifndef LEVEL_H
#define LEVEL_H

/*
    Describes the level of the game
*/
	
#include "camera_view.h"

class Level  {
    static const byte levelsNoOfColumns[noOfLevels];    
    static const byte levelsTimeAvailable[noOfLevels];
    static const byte levelsCoinValue[noOfLevels];
    static const byte levelsNoOfCoins[noOfLevels];
    static const TexturesProbability levelsTexturesProbability[noOfLevels];

    byte levelId = 0;
    byte noOfColumns;
	byte time;
    byte coinValue;
    byte noOfCoins;

    TexturesProbability texturesProbability;

    static const byte maxAdditionalColumns = 30;
    static const byte maxNoOfCoins = 10;

    byte additionalColumns[maxAdditionalColumns];
    byte additionalCoins[maxAdditionalColumns];

    // used to generate new levels
    byte nextMapColumns[matrixSize];
    byte nextCoinsColumns[matrixSize];

    struct ErasedCoin {
        Point panCameraPos;
        Point realPos;

        ErasedCoin(Point p1 = Point(0, 0), Point p2 = Point(0, 0)) : panCameraPos(p1), realPos(p2) {}
    };
    byte headErasedCoin = 0;
    ErasedCoin erasedCoinsList[maxNoOfCoins];

    void restoreErasedCoins();

    byte firstColumnIndex = 0;
    byte lastColumnIndex = matrixSize - 1;
    CameraView initialView;

public:
    Level() {};

    ~Level() {
        restoreErasedCoins();
    }

    // construct default level 1
    void initLevel();

    byte getId() { return levelId; }
    byte getNoOfColumns() { return noOfColumns; }
    byte getNoOfCoins() { return noOfCoins; }
    byte getTime() { return time; };
    byte getCoinValue() { return coinValue; };
    TexturesProbability getTextureProbability() { return texturesProbability; };

    byte getFirstColumnIndex() { return firstColumnIndex; };
    byte getLastColumnIndex() { return lastColumnIndex; };
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

    void advanceToNextLevel();

    Level operator = (const Level& other);
};

#endif