#include "hall_of_fame.h"

ActionIndex HallOfFame::run() {
    matrix->displayAnimation(rankingAnimation);
    
    if (joystick->pressedButton())
        return menuActionIndex;

    noOfScores = eepromObj->getNoOfScores();
    
    if (noOfScores == 0)
        lcd->displayText("Scoreboard clean", " No score saved ");
    else {
        if (noOfScores == 1)
            lcd->displayText(" Top 1 player ", eepromObj->read(currentDisplayedScore));
        else if (noOfScores == 2)
            lcd->displayText(" Top 2 players ", eepromObj->read(currentDisplayedScore), true);
        else
            lcd->displayText(" Top 3 players ", eepromObj->read(currentDisplayedScore), true);

        joystickUpDownMove move = joystick->movedUpDown();

        if (move == Up)
            currentDisplayedScore = (currentDisplayedScore + noOfScores - 1) % noOfScores;
        else if (move == Down)
            currentDisplayedScore = (currentDisplayedScore + 1) % noOfScores;
    }

    return hallOfFameActionIndex;
}