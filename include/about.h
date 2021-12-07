#ifndef ABOUT_H
#define ABOUT_H

#include <Arduino.h>
#include "action.h"

class About : public Action {
    char *firstLine = "Mini Super Mario by Alexandru Tifui";
    char *secondLine = "source code: https://github.com/tifui-alexandru/MiniSuperMario";

    int firstLineLength = 35;
    int secondLineLength = 62;

    int startIndexFirstLine = 0;
    int startIndexSecondLine = 0;

    unsigned long lastCountTime = 0;
    const unsigned long scrollInterval = 1000;

public : About(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix){};
    ActionIndex run() override;
};

#endif