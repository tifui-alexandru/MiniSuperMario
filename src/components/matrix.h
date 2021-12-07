#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include "LedControl.h"

#include "../../include/utils.h"

#include "../game/camera_view.h"

class Matrix {
    const byte dinPin = 12;
    const byte clockPin = 11;
    const byte loadPin = 10;
    LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER
    CameraView view;

    byte matrixBrightness = 2;

    void displayMap();

public:
    Matrix() {};
    void initSetup();
    void updateDisplay(Point currentPosition, Point lastPosition);
};

#endif