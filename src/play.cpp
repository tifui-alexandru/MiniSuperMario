#include "../include/play.h"

ActionIndex Play::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    lcd->displayText("PLAY", "GAME");

    return playActionIndex;
}