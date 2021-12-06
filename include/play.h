#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"

class Play : public Action {
public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix) {}
    ActionIndex run() override;
};

#endif