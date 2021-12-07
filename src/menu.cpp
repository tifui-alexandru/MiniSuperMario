#include <Arduino.h>
#include "../include/menu.h"

ActionIndex Menu::run() {
    lcd->displayText(firstLine, options[currentOption]);

    if (joystick->pressedButton()) 
        return optionsActionIndex[currentOption];

    updateOption();
    return menuActionIndex;
}

void Menu::updateOption() {
    joystickUpDownMove move = joystick->movedUpDown();

    if (move == Up)
        currentOption = (currentOption + noOfOptions - 1) % noOfOptions;
    else if (move == Down)
        currentOption = (currentOption + 1) % noOfOptions;
}