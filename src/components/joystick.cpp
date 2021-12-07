#include "joystick.h"

void Joystick::initSetup() {
    pinMode(buttonPin, INPUT_PULLUP);
}

bool Joystick::movedUp() {
    int yValue = analogRead(yPin);
    return yValue < minTreshold;
}

bool Joystick::movedDown() {
    int yValue = analogRead(yPin);
    return yValue > maxTreshold;
}

bool Joystick::movedLeft() {
    int xValue = analogRead(xPin);
    return xValue < minTreshold;
}

bool Joystick::movedRight() {
    int xValue = analogRead(xPin);
    return xValue > maxTreshold;
}

joystickUpDownMove Joystick::movedUpDown() {
    if (movedUp() and joystickMovedUpDown == false) {
        joystickMovedUpDown = true;
        return Up;
    }

    if (movedDown() and joystickMovedUpDown == false) {
        joystickMovedUpDown = true;
        return Down;
    }

    if (!movedDown() and !movedUp()) 
        joystickMovedUpDown = false;

    return NoneUpDown;
}

joystickLeftRightMove Joystick::movedLeftRight() {
    if (movedLeft() and joystickMovedLeftRight == false) {
        joystickMovedLeftRight = true;
        return Left;
    }

    if (movedRight() and joystickMovedLeftRight == false) {
        joystickMovedLeftRight = true;
        return Right;
    }

    if (!movedLeft() and !movedRight()) 
        joystickMovedLeftRight = false;

    return NoneLeftRight;
}

bool Joystick::pressedButton() {
    currentButtonReading = digitalRead(buttonPin);
    unsigned long now = millis();

    if (currentButtonReading != lastButtonReading) 
        lastDebounceTime = now;


    if (now - lastDebounceTime > debounceInterval and currentButtonReading != currentButtonState)
        currentButtonState = currentButtonReading;

    bool retValue = false;
    if (currentButtonState == LOW and lastButtonState == HIGH)
        retValue = true;

    lastButtonReading = currentButtonReading;
    lastButtonState = currentButtonState;

    return retValue;
}