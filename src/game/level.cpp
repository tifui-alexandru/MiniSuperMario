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
}

Level Level::operator = (const Level& other) {
    this->time = other.getTime();
    this->id = other.getId();
    this->firstColumnIndex = other.getFirstColumnIndex();
    this->lastColumnIndex = other.getLastColumnIndex();
    this->initialView = other.getInitialView();

    return *this;
}