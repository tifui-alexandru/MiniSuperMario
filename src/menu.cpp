#include <Arduino.h>
#include "../include/menu.h"

ActionIndex Menu::run() {
    lcd->displayText(firstLine, options[currentOption]);
    updateOption();
    return menuActionIndex;
}

void Menu::updateOption() {
    if (joystick->movedUp()) 
        currentOption = (currentOption + noOfOptions - 1) % noOfOptions;
    else if (joystick->movedDown()) 
        currentOption = (currentOption + 1) % noOfOptions;
}