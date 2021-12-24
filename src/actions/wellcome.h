#ifndef WELLCOME_H
#define WELLCOME_H

/*
    Displays the wellcome message.
*/

#include <Arduino.h>
#include "action.h"

class Wellcome : public Action {
    const byte wellcomeAnimation[matrixSize] = {
        B00000000,
        B00111100,
        B01111110,
        B01111110,
        B00011000,
        B00011000,
        B00011000,
        B00011000
    };
    
    unsigned long startTime;
    const unsigned long interval = 5000;

public:
    Wellcome(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, 
        Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr, Utils* gameUtils = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj, gameUtils), startTime(millis()) {}

    virtual ~Wellcome() {};
        
    ActionIndex run() override;
};

#endif