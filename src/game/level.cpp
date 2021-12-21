#include "level.h"

const byte Level::levelsNoOfColumns[noOfLevels] = {5, 10, 15, 20, 30};
const byte Level::levelsTimeAvailable[noOfLevels] = {999, 999, 999, 999, 999};
const byte Level::levelsCoinValue[noOfLevels] = {100, 200, 300, 400, 500};
const byte Level::levelsNoOfCoins[noOfLevels] = {3, 5, 10, 15, 20};
const TexturesProbability Level::levelsTexturesProbability[noOfLevels] = {
    TexturesProbability(0.33, 0.33, 0.33),
    TexturesProbability(0.33, 0.33, 0.33),
    TexturesProbability(0.33, 0.33, 0.33),
    TexturesProbability(0.33, 0.33, 0.33),
    TexturesProbability(0.33, 0.33, 0.33)
};
const float Level::levelsSpecialWallsProbability[noOfLevels] = {0, 0, 0.2, 0, 0.5};
const float Level::levelsSpecialFloorProbability[noOfLevels] = {0, 0, 0, 0.2, 0.5};

void Level::initLevel() {
    noOfColumns = levelsNoOfColumns[levelId];
    time = levelsTimeAvailable[levelId];
    coinValue = levelsCoinValue[levelId];
    noOfCoins = levelsNoOfCoins[levelId];

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

    initialView.changeMap(mapColumns, coinsColumns);

    additionalColumns[0] = gameFloor;
    additionalColumns[1] = hole;
    additionalColumns[2] = hole;
    additionalColumns[3] = hole;
    additionalColumns[4] = endWall;

    additionalCoins[0] = noCoin;
    additionalCoins[1] = coinCol4;
    additionalCoins[2] = noCoin;
    additionalCoins[3] = coinCol4;
    additionalCoins[4] = noCoin;
}

bool Level::hasNextColumn() {
    return lastColumnIndex - matrixSize < noOfColumns - 1;
}

bool Level::hasPrevColumn() {
    return firstColumnIndex > 0;
}

void Level::moveCameraRight() {
    ++firstColumnIndex; 
    ++lastColumnIndex;
}

void Level::moveCameraLeft() {
    --firstColumnIndex;
    --lastColumnIndex;
}

byte Level::getNextColumn() {
    byte actualColumnIndex = lastColumnIndex + 1;
    return additionalColumns[actualColumnIndex - matrixSize];
}

byte Level::getPrevColumn() {
    byte actualColumnIndex = firstColumnIndex - 1;

    if (actualColumnIndex < matrixSize)
        return initialView.getMapColumn(matrixSize - actualColumnIndex - 1); // complementar position due to matrix logic
    else
        return additionalColumns[actualColumnIndex - matrixSize];
}

byte Level::getNextCoinsColumn() {
    byte actualColumnIndex = lastColumnIndex + 1;
    return additionalCoins[actualColumnIndex - matrixSize];
}

byte Level::getPrevCoinsColumn() {
    byte actualColumnIndex = firstColumnIndex - 1;

    if (actualColumnIndex < matrixSize)
        return initialView.getCoinsColumn(matrixSize - actualColumnIndex - 1); // complementar position due to matrix logic
    else
        return additionalCoins[actualColumnIndex - matrixSize];
}

bool Level::reachedEndOfTheLevel() {
    return lastColumnIndex - matrixSize  == noOfColumns - 1;
}

void Level::restartLevel() {
    firstColumnIndex = 0;
    lastColumnIndex = matrixSize - 1;
    restoreErasedCoins();
}

void Level::restoreErasedCoins() {
    ErasedCoin* currentCoin = headErasedCoin;
    while (currentCoin != nullptr) {
        if (currentCoin->realPos.y < matrixSize) {
            // complementar position due to matrix logic
            initialView.setCoin({currentCoin->panCameraPos.x, matrixSize - currentCoin->panCameraPos.y - 1});
        }
        else {
            byte index = currentCoin->realPos.y - matrixSize;
            byte line = matrixSize - currentCoin->realPos.x - 1;
            byte setMask = 1 << line; // zero everywhere exept on the desired line
            additionalCoins[index] |= setMask;
        }

        ErasedCoin* temp = currentCoin;
        currentCoin = currentCoin->next;
        delete temp;
    }

    headErasedCoin = nullptr;
}

void Level::eraseCoin(Point p) {
    // get point on the big map
    Point realPoint = p;
    realPoint.y = matrixSize - p.y - 1 + firstColumnIndex; // complementar position due to matrix logic

    // erase the coin
    if (realPoint.y < matrixSize) {
        initialView.eraseCoin({p.x, matrixSize - p.y - 1}); // complementar position due to matrix logic
    }
    else {
        byte index = realPoint.y - matrixSize;
        byte line = matrixSize - realPoint.x - 1;
        byte eraseMask = ((1 << matrixSize) - 1) ^ (1 << line); // one everywhere exept on the desired line
        additionalColumns[index] &= eraseMask;
        additionalCoins[index] &= eraseMask;
    }

    Serial.println("here");

    // save the coin position
    ErasedCoin* erasedCoin = new ErasedCoin(p, realPoint);
    Serial.println("here");
    erasedCoin->next = headErasedCoin;
    headErasedCoin = erasedCoin;
}

Level Level::operator = (const Level& other) {
    this->levelId = other.getId();
    this->time = other.getTime();
    this->noOfCoins = other.getNoOfCoins();
    this->noOfColumns = other.getNoOfColumns();
    this->coinValue = other.getCoinValue();

    this->texturesProbability = other.getTextureProbability();
    this->specialWallsProbability = other.getSpecialWallsProbability();
    this->specialFloorProbability = other.getSpecialFloorProbability();

    this->firstColumnIndex = other.getFirstColumnIndex();
    this->lastColumnIndex = other.getLastColumnIndex();
    this->initialView = other.getInitialView();

    return *this;
}

// assume that the current level is not final
void Level::advanceToNextLevel() {
    if (levelId == noOfLevels)
        return;

    restoreErasedCoins(); // in order to free some memory

    ++levelId;

    noOfColumns = levelsNoOfColumns[levelId];
    time = levelsTimeAvailable[levelId];
    coinValue = levelsCoinValue[levelId];
    noOfCoins = levelsNoOfCoins[levelId];

    texturesProbability = levelsTexturesProbability[levelId];
    specialWallsProbability = levelsSpecialWallsProbability[levelId];
    specialFloorProbability = levelsSpecialFloorProbability[levelId];

    byte totalColumns = noOfColumns + matrixSize;

    // generate the map

    // initialize the new map
    for (byte col = 0; col < totalColumns; ++col) {
        if (col < matrixSize) {
            nextMapColumns[col] = hole;
            nextCoinsColumns[col] = noCoin;
        }
        else {
            additionalColumns[col - matrixSize] = hole;
            additionalCoins[col - matrixSize] = noCoin;
        }
    }

    // first 4 columns are floor
    // we don't want mario to spawn direcrly into an obstacle
    for (byte col = 0; col < 4; ++col)
        nextMapColumns[col] = gameFloor;

    for (byte col = 4; col < totalColumns - 1; ++col) {
        byte texture = texturesProbability.generateTexture();

        // if (texture != gameFloor and texture != hole and random(100) < specialWallsProbability * 100)
        // if (textture == gameFloor and random(100) < specialFloorProbability * 100)

        if (col < matrixSize)
            nextMapColumns[col] = texture;
        else 
            additionalColumns[col - matrixSize] = texture;
    }

    // last column is the end wall
    additionalColumns[noOfColumns - 1] = endWall;

    // generate coin positions
    for (byte coinIdx = 0; coinIdx < noOfCoins; ++coinIdx) {
        // generate positions until we get a valid one
        while (true) {
            byte newCoinRow = random(coinTypes);
            byte newCoinColumn = random(4, totalColumns); // spawn coins begining to the 4th column

            byte coinTexture = noCoin;
            if (newCoinRow == 1)
                coinTexture = coinCol2;
            else if (newCoinRow == 2)
                coinTexture = coinCol2;
            else if (newCoinRow == 3)
                coinTexture = coinCol3;
            else if (newCoinRow == 4)
                coinTexture = coinCol4;
            else if (newCoinRow == 5)
                coinTexture = coinCol5;

            byte virtualMapColumn;
            byte virtualCoinColumn;
            if (newCoinColumn < matrixSize) {
                virtualMapColumn = nextMapColumns[newCoinColumn];
                virtualCoinColumn = nextCoinsColumns[newCoinColumn];
            }
            else {
                virtualMapColumn = additionalColumns[newCoinColumn - matrixSize];
                virtualCoinColumn = additionalCoins[newCoinColumn - matrixSize];
            }

            // if the coin position is free we found a valid position
            // set the coin and exit the while loop
            if ((virtualMapColumn & coinTexture) == 0 and (virtualCoinColumn & coinTexture) == 0)
            {
                if (newCoinColumn < matrixSize)
                    nextCoinsColumns[newCoinColumn] |= coinTexture;
                else
                    additionalCoins[newCoinColumn - matrixSize] |= coinTexture;
                break;
            }
        }
    }

    initialView.changeMap(nextMapColumns, nextCoinsColumns);
    restartLevel();
}