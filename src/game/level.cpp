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
        return initialView.getColumn(firstColumnIndex);
    else
        return additionalColumns[firstColumnIndex - matrixSize];
}