#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include "LedControl.h"

#include "../../include/utils.h"
#include "../game/level.h"

class Matrix {
    const byte dinPin = 12;
    const byte clockPin = 11;
    const byte loadPin = 10;
    LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER

    byte matrixBrightness = 2;

public:
    Matrix() {};
    void initSetup();
    
    byte getMatrixBrightness() { return matrixBrightness; };
    void setMatrixBrightness(byte);
    
    void updateDisplay(Point, Point, CameraView&);
    void displayMap(CameraView&);
};

#endif