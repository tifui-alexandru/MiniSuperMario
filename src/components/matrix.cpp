#include "matrix.h"

void Matrix::initSetup() {
    // the zero refers to the MAX7219 number, it is zero for 1 chip
    lc.shutdown(0, false);                // turn off power saving, enables display
    lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
    lc.clearDisplay(0);                   // clear screen
    displayMap();                         // print the initial configuration
}

void Matrix::updateDisplay(Point currentPosition, Point lastPosition) {
    // update position
    byte removeMask = ((1 << matrixSize) - 1) ^ (1 << lastPosition.y); // one everywhere exept one position
    byte addMask = 1 << currentPosition.y;                            // zero everywhere exept one position

    matrixByte[lastPosition.x] &= removeMask;
    matrixByte[currentPosition.x] |= addMask; 

    // display map
    displayMap();
}

void Matrix::displayMap() {
    for (int row = 0; row < matrixSize; ++row)
        lc.setRow(0, row, matrixByte[row]);
}