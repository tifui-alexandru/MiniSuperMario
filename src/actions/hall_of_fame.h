#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H

#include <Arduino.h>
#include "action.h"

class HallOfFame : public Action {
    byte noOfScores = 0;
    byte currentDisplayedScore = 0;

    static char* secondLine[3];

public:
    HallOfFame(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};

    virtual ~HallOfFame() {}

    ActionIndex run() override;
};

#endif