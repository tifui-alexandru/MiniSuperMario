#include "settings.h"

ActionIndex Settings::run() {
    if (int(currentState) < noOfOptions)
        lcd->displayText(options[(int(currentState))], emptyLcdLine);

    if (currentState == startLevel)
        return runStartLevel();
    else if (currentState == lcdContrast)
        return runLcdContrast();
    else if (currentState == lcdBrightness)
        return runLcdBrightness();
    else if (currentState == matrixIntensity)
        return runMatrixIntensity();
    else if (currentState == changeNickname)
        return runChangeNickname();
    else if (currentState == backToMenu)
        return runBackToMenu();
    else
        return runDefaultScreen();
}

void Settings::updateOption() {
    joystickUpDownMove move = joystick->movedUpDown();

    if (move == Up)
        currentOption = (currentOption + noOfOptions - 1) % noOfOptions;
    else if (move == Down)
        currentOption = (currentOption + 1) % noOfOptions;
}

ActionIndex Settings::runStartLevel() {

}

ActionIndex Settings::runLcdContrast() {

}

ActionIndex Settings::runLcdBrightness() {

}

ActionIndex Settings::runMatrixIntensity() {

}

ActionIndex Settings::runChangeNickname() {

}

ActionIndex Settings::runBackToMenu() {
    currentState = defaultScreen;
    currentOption = 0;
    return menuActionIndex;
}

ActionIndex Settings::runDefaultScreen() {
    lcd->displayText(defaultFirstLine, options[currentOption]);
    updateOption();

    if (joystick->pressedButton())
        currentState = SettingsState(currentOption);

    return settingsActionIndex;
}