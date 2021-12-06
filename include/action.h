#ifndef ACTION_H
#define ACTION_H

#include <Arduino.h>
#include "lcd.h";
#include "joystick.h";
#include "matrix.h";
#include "utils.h"

class Action {
protected:
    Lcd* lcd;
    Joystick* joystick;
    Matrix* matrix;
public:
    Action();
    virtual ActionIndex run() = 0;
    void initSetup();
};

#endif