#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// matrix constants
static const byte matrixSize = 8;
static const byte matrixMinIntensity = 0;
static const byte matrixMaxIntensity = 15;

// lcd constants
static char* emptyLcdLine = "                ";
static byte lcdMinContrast = 0;
static byte lcdMaxContrast = 1;
static byte lcdMinIntensity = 0;
static byte lcdMaxIntensity = 1;

// levels from 1 to noOfLevels
const int noOfLevels = 5;
static int utilsStartingLevel = 1; 


struct Point {
    byte x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator == (const Point& other) const {
        return x == other.x and y == other.y;
    }

    bool operator != (const Point& other) const {
        return x != other.x or y != other.y;
    }

    Point operator = (const Point& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

enum joystickUpDownMove {
    Up,
    Down,
    NoneUpDown
};

enum joystickLeftRightMove {
    Left,
    Right,
    NoneLeftRight
};

enum ActionIndex {
    wellcomeActionIndex,
    menuActionIndex,
    playActionIndex,
    howToPlayActionIndex,
    hallOfFameActionIndex,
    settingsActionIndex,
    aboutActionIndex,
    registerActionIndex
};

#endif