#ifndef ABOUT_H
#define ABOUT_H

#include <Arduino.h>
#include "action.h"

class About : public Action {
    char *firstLine = "Mini Super Mario";
    char *secondLine = " Creator: Alexandru Tifui source code: https://github.com/tifui-alexandru/MiniSuperMario ";

    int secondLineLength = 89;
    int startIndexSecondLine = 0;

    unsigned long lastCountTime = 0;
    const unsigned long scrollInterval = 400;

public : About(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix){};
    ActionIndex run() override;
};

#endif