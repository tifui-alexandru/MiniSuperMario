#ifndef MATRIX_H
#define MATRIX_H

/*
    Manipulates the matrix.
*/

#include <Arduino.h>
#include "LedControl.h"

#include "utils.h"
#include "../game/level.h"

#include "eeprom.h"

class Matrix {
    const byte dinPin = 12;
    const byte clockPin = 11;
    const byte loadPin = 10;
    LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER

    byte matrixBrightness = 2;

    const byte lightUpByte = B11111111;
    const byte lightDownByte = 0;

    const unsigned long blinkingInterval = 300;
    unsigned long lastBlink = 0;
    bool blinkingState = false;

    public : Matrix(){};
    void initSetup(EepromClass*);
    
    byte getMatrixBrightness() { return matrixBrightness; };
    void setMatrixBrightness(byte, EepromClass*);
    
    void updateDisplay(Point, Point, CameraView&);
    void displayMap(CameraView&);

    void lightUp();
    void lightDown();

    void displayAnimation(const byte*);
};

#endif