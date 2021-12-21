#ifndef WELLCOME_H
#define WELLCOME_H

#include <Arduino.h>
#include "action.h"

class Wellcome : public Action {
    unsigned long startTime;
    const unsigned long interval = 5000;

public:
    Wellcome(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj), startTime(millis()) {};
        
    ActionIndex run() override;
};

#endif