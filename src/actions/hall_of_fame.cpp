#include "hall_of_fame.h"

ActionIndex HallOfFame::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    noOfScores = eepromObj->getNoOfScores();
    
    if (noOfScores == 0)
        lcd->displayText(" Top 3 players ", " No score saved ");
    else {
        // not testet yet
        lcd->displayText(" Top 3 players ", eepromObj->read(currentDisplayedScore));

        joystickUpDownMove move = joystick->movedUpDown();

        if (move == Up)
            currentDisplayedScore = (currentDisplayedScore + noOfScores - 1) % noOfScores;
        else if (move == Down)
            currentDisplayedScore = (currentDisplayedScore + 1) % noOfScores;
    }

    return hallOfFameActionIndex;
}