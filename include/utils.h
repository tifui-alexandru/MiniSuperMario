#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

const static byte matrixSize = 8;

static char* emptyLcdLine = "                ";

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