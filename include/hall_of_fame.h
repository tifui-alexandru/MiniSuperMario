#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H

#include <Arduino.h>
#include "action.h"

class HallOfFame : public Action {
    char* firstLine = " Top 3 players ";
    char* defaultText = " No score saved ";

    char* secondLine[3];

public:
    HallOfFame(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix) {};
    ActionIndex run() override;
};

#endif