#ifndef LEVEL_H
#define LEVEL_H
	
#include "camera_view.h"

class Level  {
    static const byte levelsNoOfColumns[noOfLevels];    
    static const byte levelsTimeAvailable[noOfLevels];
    static const byte levelsCoinValue[noOfLevels];
    static const byte levelsNoOfCoins[noOfLevels];
    static const TexturesProbability levelsTexturesProbability[noOfLevels];
    static const float levelsSpecialWallsProbability[noOfLevels];
    static const float levelsSpecialFloorProbability[noOfLevels];

    byte levelId = 0;
    byte noOfColumns;
	byte time;
    byte coinValue;
    byte noOfCoins;

    TexturesProbability texturesProbability;
    float specialWallsProbability;
    float specialFloorProbability;

    static const byte maxAdditionalColumns = 30;

    byte additionalColumns[maxAdditionalColumns];
    byte additionalCoins[maxAdditionalColumns];

    // used to generate new levels
    byte nextMapColumns[matrixSize];
    byte nextCoinsColumns[matrixSize];

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

    // construct default level 1
    void initLevel();

    byte getId() { return levelId; }
    byte getNoOfColumns() { return noOfColumns; }
    byte getNoOfCoins() { return noOfCoins; }
    byte getTime() { return time; };
    byte getCoinValue() { return coinValue; };
    TexturesProbability getTextureProbability() { return texturesProbability; };
    float getSpecialWallsProbability() { return specialWallsProbability; };
    float getSpecialFloorProbability() { return specialFloorProbability; };


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

    void advanceToNextLevel();

    Level operator = (const Level& other);
};

#endif