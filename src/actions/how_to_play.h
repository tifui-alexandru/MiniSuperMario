#ifndef HOW_TO_PLAY_H
#define HOW_TO_PLAY_H

#include <Arduino.h>
#include "action.h"

class HowToPlay : public Action {
    byte questionAnimation[matrixSize] = {
        B00111100,
        B01000010,
        B01000010,
        B00000100,
        B00011000,
        B00010000,
        B00000000,
        B00010000
    };

public:
    HowToPlay(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, 
        Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr, Utils* gameUtils = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj, gameUtils) {}

    virtual ~HowToPlay() {};
        
    ActionIndex run() override;
};

#endif