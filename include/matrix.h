#include <Arduino.h>
#include "LedControl.h"
#include "utils.h"

class Matrix {
    const byte dinPin = 12;
    const byte clockPin = 11;
    const byte loadPin = 10;
    LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER

    byte matrixBrightness = 2;

    byte matrixByte[matrixSize] = {
        B10000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    void displayMap();

public:
    Matrix();
    void initSetup();
    void updateDisplay(Point currentPosition, Point lastPosition);
};