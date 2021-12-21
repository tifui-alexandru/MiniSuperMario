#include "matrix.h"

void Matrix::setMatrixBrightness(byte newVal, EepromClass* eepromObj) {
    matrixBrightness = newVal;
    lc.setIntensity(0, matrixBrightness);
    eepromObj->writeMatrixIntensity(matrixBrightness);
}

void Matrix::initSetup(EepromClass* eepromObj) {
    matrixBrightness = eepromObj->readMatrixIntensity();

    if (matrixBrightness < matrixMinIntensity or matrixBrightness > matrixMaxIntensity) 
        matrixBrightness = (matrixMinIntensity + matrixMaxIntensity) / 2;

    // the zero refers to the MAX7219 number, it is zero for 1 chip
    lc.shutdown(0, false);                // turn off power saving, enables display
    lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
    lc.clearDisplay(0);                   // clear screen
}

// void Matrix::updateDisplay(Point currentPosition, Point lastPosition, CameraView& view) {
//     // update position
//     view.setPosition(lastPosition, false);
//     view.setPosition(currentPosition, true);

//     // display map
//     displayMap(view);
// }

void Matrix::displayMap(CameraView& view) {
    unsigned long now = millis();
    if (now - lastBlink > blinkingInterval) {
        lastBlink = now;
        blinkingState = !blinkingState;
        view.changeCoinsState(blinkingState);
    }

    for (byte row = 0; row < matrixSize; ++row)
        lc.setRow(0, row, view.getMapRow(row));
}

void Matrix::lightUp() {
    for (byte row = 0; row < matrixSize; ++row)
        lc.setRow(0, row, lightUpByte);
}

void Matrix::lightDown() {
    for (byte row = 0; row < matrixSize; ++row)
        lc.setRow(0, row, lightDownByte);
}