#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"
#include "../game/level.h"

class Play : public Action {
    const int maxLives = 3;
    const int maxTime = 1000; // in seconds
    const int noOfLevels = 5;

    int lives = maxLives;
    int score = 0;

    Level* level;

public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj), level(new Level()) {};
        
    ActionIndex run() override;
};

#endif