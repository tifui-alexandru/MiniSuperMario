#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include "LedControl.h"

#include "../../include/utils.h"
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

    const byte happyAnimation[matrixSize] = {
        B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10100101,
        B10011001,
        B01000010,
        B00111100,
    };

    const byte sadAnimation[matrixSize] = {
        B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10011001,
        B10100101,
        B01000010,
        B00111100
    };

    const byte menuAnimation[matrixSize] = {
        B00111100,
        B01000010,
        B10100101,
        B10111101,
        B10100101,
        B10100101,
        B01000010,
        B00111100
    };

    const byte settingsAnimation[matrixSize] = {
        B00011000,
        B00111100,
        B01000010,
        B11011011,
        B11011011,
        B01000010,
        B00111100,
        B00011000
    };

    public : Matrix(){};
    void initSetup(EepromClass*);
    
    byte getMatrixBrightness() { return matrixBrightness; };
    void setMatrixBrightness(byte, EepromClass*);
    
    void updateDisplay(Point, Point, CameraView&);
    void displayMap(CameraView&);

    void lightUp();
    void lightDown();

    void displayMenuAnimation();
    void displaySettingAnimation();
    void displayHappyAnimation();
    void displaySadAnimation();
};

#endif