#ifndef ABOUT_H
#define ABOUT_H

#include <Arduino.h>
#include "action.h"

class About : public Action {
public:
    About(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr) : Action(lcd, joystick, matrix) {};
    ActionIndex run() override;
};

#endif