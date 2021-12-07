#ifndef ACTION_H
#define ACTION_H

#include <Arduino.h>
#include "../components/lcd.h";
#include "../components/joystick.h";
#include "../components/matrix.h";
#include "../components/buzzer.h"
#include "../components/eeprom.h"

#include "../../include/utils.h"

class Action {
protected:
    Lcd* lcd;
    Joystick* joystick;
    Matrix* matrix;
    Buzzer* buzzer;
    EepromClass* eepromObj;

public:
    Action(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr) : 
        lcd(lcd), joystick(joystick), matrix(matrix), buzzer(buzzer), eepromObj(eepromObj) {};
        
    virtual ActionIndex run() = 0;
};

#endif