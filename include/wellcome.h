#ifndef WELLCOME_H
#define WELLCOME_H

#include <Arduino.h>
#include "action.h"

class Wellcome : public Action {
    char* msgLine1 = "Welcome to";
    char* msgLine2 = "Mini Super Mario!";
    unsigned long startTime;
    const unsigned long interval = 5000;

public:
    Wellcome(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr) : Action(lcd, joystick, matrix), startTime(millis()) {};
    ActionIndex run() override;
    // void initSetup();
};

#endif