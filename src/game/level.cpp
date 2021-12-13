#include "level.h"  

bool Level::hasNextColumn() {
    return lastColumnIndex - matrixSize < noOfColumns - 1;
}

bool Level::hasPrevColumn() {
    return firstColumnIndex > 0;
}

byte Level::getNextColumn() {
    ++firstColumnIndex;
    ++lastColumnIndex;
    return additionalColumns[lastColumnIndex - matrixSize];
}

byte Level::getPrevColumn() {
    --firstColumnIndex;
    --lastColumnIndex;

    if (firstColumnIndex < matrixSize) 
        return initialView.getMapColumn(firstColumnIndex);
    else
        return additionalColumns[firstColumnIndex - matrixSize];
}

// always called after Level::getNextColumn()
byte Level::getNextCoinsColumn() {
    return additionalCoins[lastColumnIndex - matrixSize];
}

// always called after Level::getPrevColumn()
byte Level::getPrevCoinsColumn() {
    if (firstColumnIndex < matrixSize)
        return initialView.getCoinsColumn(firstColumnIndex);
    else
        return additionalCoins[firstColumnIndex - matrixSize];
}

bool Level::reachedEndOfTheLevel() {
    return lastColumnIndex - matrixSize  == noOfColumns - 1;
}

Level Level::operator = (const Level& other) {
    this->time = other.getTime();
    this->id = other.getId();
    this->firstColumnIndex = other.getFirstColumnIndex();
    this->lastColumnIndex = other.getLastColumnIndex();
    this->initialView = other.getInitialView();

    return *this;
}