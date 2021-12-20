#include "level.h"

const byte Level::levelsNoOfColumns[noOfLevels] = {5, 10, 15, 20, 30};
const byte Level::levelsTimeAvailable[noOfLevels] = {999, 999, 999, 999, 999};
const byte Level::levelsCoinValue[noOfLevels] = {100, 200, 300, 400, 500};
const byte Level::levelsNoOfCoins[noOfLevels] = {3, 5, 10, 15, 20};

void Level::initLevel() {
    noOfColumns = levelsNoOfColumns[0];
    time = levelsTimeAvailable[0];
    coinValue = levelsCoinValue[0];
    noOfCoins = levelsNoOfCoins[0];

    delete[] additionalColumns;
    delete[] additionalCoins;

    additionalColumns = new byte[noOfColumns];
    additionalCoins = new byte[noOfColumns];

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

    // restore erased coins
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

    // save the coin position
    ErasedCoin* erasedCoin = new ErasedCoin(p, realPoint);
    erasedCoin->next = headErasedCoin;
    headErasedCoin = erasedCoin;
}

Level Level::operator = (const Level& other) {
    this->time = other.getTime();
    this->noOfCoins = other.getNoOfCoins();
    this->noOfColumns = other.getNoOfColumns();
    this->coinValue = other.getCoinValue();

    this->firstColumnIndex = other.getFirstColumnIndex();
    this->lastColumnIndex = other.getLastColumnIndex();
    this->initialView = other.getInitialView();

    return *this;
}

Level Level::getNewLevel() {
    return *this; // for now
    // set the ground for generating the new levels
}