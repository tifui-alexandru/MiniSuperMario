#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "utils.h"

class Joystick {
    const byte xPin = A0;
    const byte yPin = A1;

    Point currentPosition;
    Point lastPosition;

    enum moveDirection {
        Up,
        Down,
        Right,
        Left
    } lastMoveDirection;
    
    bool changedDirectionUp();
    bool changedDirectionDown();
    bool changedDirectionRight();
    bool changedDirectionLeft();

    const int minTreshold = 200;
    const int maxTreshold = 600;

    unsigned long long lastMoved = 0;
    const int moveInterval = 100;

    Point updatePosition();

public:
    Joystick() {};
    bool moved();

    bool movedUp();
    bool movedDown();
    bool movedRight();
    bool movedLeft();
    bool pressed();

    Point getCurrentPosition() const;
    Point getLastPosition() const;
};

#endif