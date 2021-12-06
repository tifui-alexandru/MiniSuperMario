#include <Arduino.h>
#include "utils.h"

class Joystick {
    const byte xPin = A0;
    const byte yPin = A1;

    Point currentPosition = {0, 7};
    Point lastPosition;

    const int minTreshold = 200;
    const int maxTreshold = 600;

    unsigned long long lastMoved = 0;
    const int moveInterval = 100;

    Point updatePosition();

public:
    Joystick();
    bool moved();

    Point getCurrentPosition() const;
    Point getLastPosition() const;
};