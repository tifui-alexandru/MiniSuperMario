#include "../include/hall_of_fame.h"

ActionIndex HallOfFame::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    lcd->displayText("Hall of fame", "highscore");

    return hallOfFameActionIndex;
}