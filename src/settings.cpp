#include "../include/settings.h"

ActionIndex Settings::run() {
    if (joystick->pressedButton())
        return menuActionIndex;

    lcd->displayText("Setting", "good luck");

    return settingsActionIndex;
}