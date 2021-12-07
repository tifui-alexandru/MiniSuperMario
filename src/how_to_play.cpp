#include "../include/how_to_play.h"

ActionIndex HowToPlay::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    lcd->displayText("Instructions", "how to play");

    return howToPlayActionIndex;
}