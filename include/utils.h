#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

struct Point {
    byte x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator == (const Point& other) const {
        return x == other.x and y == other.y;
    }

    bool operator != (const Point& other) const {
        return x != other.x or y != other.y;
    }
};

const static byte matrixSize = 8;

#endif