#ifndef ABOUT_H
#define ABOUT_H

#include <Arduino.h>
#include "action.h"

class About : public Action {
    const byte infoAnimation[matrixSize] = {
        B00000000,
        B00011000,
        B00011000,
        B00000000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
    };

    byte secondLineLength = 89;
    byte startIndexSecondLine = 0;

    unsigned long lastCountTime = 0;
    const unsigned long scrollInterval = 400;

public :
    About(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, 
        Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr, Utils* gameUtils = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj, gameUtils) {}

    virtual ~About() {}

    ActionIndex run() override;
};

#endif