#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H

#include <Arduino.h>
#include "action.h"

class HallOfFame : public Action {
    char* firstLine = " Top 3 players ";
    char* defaultText = " No score saved ";

    int noOfScores = 0;
    int currentDisplayedScore = 0;

    char* secondLine[3];

public:
    HallOfFame(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};

    ActionIndex run() override;
};

#endif