#include "include/matrix.h"
#include "include/joystick.h"

Matrix gameMap;
Joystick joystick;

void setup() {
    gameMap.initSetup();
}

void loop() {
    if (joystick.moved()) {
        gameMap.updateDisplay(joystick.getCurrentPosition(), joystick.getLastPosition());
    }
}
