#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "action.h"
#include "joystick.h"

class Menu : public Action {
    char* line1 = "Options: "; // up and down emoji
    static const byte noOfOptions = 5;
    char* options[noOfOptions] = {
        "Start game",
        "How to play",
        "Hall of fame",
        "Settings",
        "About"
    };

    byte currentOption = 0;

public:
    Menu();
    ActionIndex run() override;
};

#endif