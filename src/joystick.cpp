#include "../include/joystick.h"

Joystick::Joystick() {}

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
    int xValue = analogRead(xPin);
    int yValue = analogRead(yPin);

    lastPosition = currentPosition;

    if (xValue < minTreshold)
        currentPosition.x = (currentPosition.x + matrixSize - 1) % matrixSize;

    if (xValue > maxTreshold)
        currentPosition.x = (currentPosition.x + 1) % matrixSize;

    if (yValue < minTreshold)
        currentPosition.y = (currentPosition.y + matrixSize - 1) % matrixSize;

    if (yValue > maxTreshold)
        currentPosition.y = (currentPosition.y + 1) % matrixSize;

    if (currentPosition != lastPosition)
        return currentPosition;
    else
        return {-1, -1};
}