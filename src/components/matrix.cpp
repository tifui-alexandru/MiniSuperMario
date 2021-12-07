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
    view.setPosition(lastPosition, false);
    view.setPosition(currentPosition, true);

    // display map
    displayMap();
}

void Matrix::displayMap() {
    for (int row = 0; row < matrixSize; ++row)
        lc.setRow(0, row, view.getRow(row));
}