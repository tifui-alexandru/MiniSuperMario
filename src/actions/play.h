#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"

class Play : public Action {
    const int maxLives = 3;

    int remainingLives = maxLives;
    int remainingTime = maxTime;

public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif