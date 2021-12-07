#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "../../include/utils.h"

class Joystick {
    const byte xPin = A0;
    const byte yPin = A1;
    const byte buttonPin = 8;

    const int minTreshold = 200;
    const int maxTreshold = 600;

    unsigned long lastDebounceTime = 0;
    const unsigned long debounceInterval = 30;

    bool currentButtonReading = HIGH;
    bool lastButtonReading = HIGH;

    bool lastButtonState = LOW;
    bool currentButtonState = LOW;

    bool joystickMovedUpDown = false;
    bool joystickMovedLeftRight = false;

    bool movedUp();
    bool movedDown();
    bool movedRight();
    bool movedLeft();

public:
    Joystick() {};
    void initSetup();
    joystickUpDownMove movedUpDown();
    joystickLeftRightMove movedLeftRight();
    bool pressedButton();
};

#endif