#ifndef MENU_H
#define MENU_H

/*
    Used to navigate through the menu.
*/

#include <Arduino.h>
#include "action.h"

class Menu : public Action {
    const byte menuAnimation[matrixSize] = {
        B00111100,
        B01000010,
        B10111101,
        B10000001,
        B10000001,
        B10111101,
        B01000010,
        B00111100,
    };

    static const byte noOfOptions = 5;

    char* options[noOfOptions] = {
        "Start game",
        "How to play",
        "Hall of fame",
        "Settings",
        "About"
    };

    ActionIndex optionsActionIndex[noOfOptions] = {
        playActionIndex,
        howToPlayActionIndex,
        hallOfFameActionIndex,
        settingsActionIndex,
        aboutActionIndex
    };

    byte currentOption = 0;

public:
    Menu(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, 
        Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr, Utils* gameUtils = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj, gameUtils) {}

    virtual ~Menu() {}
        
    ActionIndex run() override;
    void updateOption();
};

#endif