#include "how_to_play.h"

ActionIndex HowToPlay::run() {
    matrix->displayAnimation(questionAnimation);

    if (joystick->pressedButton()) {
        buzzer->beep();
        return menuActionIndex;
    }

    lcd->displayText("Instructions", "how to play");

    return howToPlayActionIndex;
}