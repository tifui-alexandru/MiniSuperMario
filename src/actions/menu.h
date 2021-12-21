#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "action.h"

class Menu : public Action {
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
    Menu(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
    void updateOption();
};

#endif