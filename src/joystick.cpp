#include "../include/joystick.h"

Point Joystick::getCurrentPosition() const {
    return currentPosition;
}

Point Joystick::getLastPosition() const {
    return lastPosition;
}

bool Joystick::moved() {
    if (millis() - lastMoved > moveInterval) {
        lastMoved = millis();
        Point newPoint = updatePosition();

        if (newPoint == Point(-1, -1))
            return false;
        return true;
    }
    return false;
}

Point Joystick::updatePosition() {
    lastPosition = currentPosition;

    if (changedDirectionLeft())
        currentPosition.x = (currentPosition.x + matrixSize - 1) % matrixSize;

    if (changedDirectionRight())
        currentPosition.x = (currentPosition.x + 1) % matrixSize;

    if (changedDirectionUp())
        currentPosition.y = (currentPosition.y + matrixSize - 1) % matrixSize;

    if (changedDirectionDown())
        currentPosition.y = (currentPosition.y + 1) % matrixSize;

    if (currentPosition != lastPosition)
        return currentPosition;
    else
        return {-1, -1};
}

bool Joystick::changedDirectionUp() {
    int yValue = analogRead(yPin);
    lastMoveDirection = Up;
    return yValue < minTreshold;
}

bool Joystick::changedDirectionDown() {
    int yValue = analogRead(yPin);
    lastMoveDirection = Down;
    return yValue > maxTreshold;
}

bool Joystick::changedDirectionLeft() {
    int xValue = analogRead(xPin);
    lastMoveDirection = Left;
    return xValue < minTreshold;
}

bool Joystick::changedDirectionRight() {
    int xValue = analogRead(xPin);
    lastMoveDirection = Right;
    return xValue > maxTreshold;
}

bool Joystick::movedUp() {
    if (millis() - lastMoved > moveInterval) {
        lastMoved = millis();
        return lastMoveDirection == Up;
    }
    return false;
}

bool Joystick::movedDown() {
    if (millis() - lastMoved > moveInterval) {
        lastMoved = millis();
        return lastMoveDirection == Down;
    }
    return false;
}

bool Joystick::movedRight() {
    if (millis() - lastMoved > moveInterval) {
        lastMoved = millis();
        return lastMoveDirection == Right;
    }
    return false;
}

bool Joystick::movedLeft() {
    if (millis() - lastMoved > moveInterval) {
        lastMoved = millis();
        return lastMoveDirection == Left;
    }
    return false;
}

bool Joystick::pressed() {
    return false;
}