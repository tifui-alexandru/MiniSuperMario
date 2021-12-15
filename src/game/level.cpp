#include "level.h"  

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
    this->id = other.getId();
    this->firstColumnIndex = other.getFirstColumnIndex();
    this->lastColumnIndex = other.getLastColumnIndex();
    this->initialView = other.getInitialView();

    return *this;
}