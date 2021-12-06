#ifndef HOW_TO_PLAY_H
#define HOW_TO_PLAY_H

#include <Arduino.h>
#include "action.h"

class HowToPlay : public Action {
public:
    HowToPlay(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix) {};
    ActionIndex run() override;
};

#endif