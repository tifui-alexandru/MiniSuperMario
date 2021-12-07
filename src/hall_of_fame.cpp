#include "../include/hall_of_fame.h"

ActionIndex HallOfFame::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    int noOfScores = 

    lcd->displayText("Hall of fame", "highscore");

    return hallOfFameActionIndex;
}