#include <Arduino.h>
#include "menu.h"

ActionIndex Menu::run() {
    matrix->displayAnimation(menuAnimation);
    lcd->displayText("Options: ", options[currentOption], true);

    if (joystick->pressedButton()) {
        buzzer->beep();
        return optionsActionIndex[currentOption];
    }

    updateOption();
    return menuActionIndex;
}

void Menu::updateOption() {
    joystickUpDownMove move = joystick->movedUpDown();

    if (move == Up) {
        buzzer->beep();
        currentOption = (currentOption + noOfOptions - 1) % noOfOptions;
    }
    else if (move == Down) {
        buzzer->beep();
        currentOption = (currentOption + 1) % noOfOptions;
    }
}