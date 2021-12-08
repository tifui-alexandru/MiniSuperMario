#include "settings.h"

ActionIndex Settings::run() {
    if (currentState == startLevel)
        return runStartLevel();
    else if (currentState == lcdContrast)
        return runLcdContrast();
    else if (currentState == lcdBrightness)
        return runLcdBrightness();
    else if (currentState == matrixIntensity)
        return runMatrixIntensity();
    else if (currentState == changeNickname)
        return exitRoutine(registerActionIndex);
    else if (currentState == backToMenu)
        return exitRoutine(menuActionIndex);
    else
        return runDefaultScreen();
}

int Settings::getJoystickMove(int lowerBound, int upperBound, int value) {
    int returnValue = value;

    joystickUpDownMove move = joystick->movedUpDown();

    if (move == Up) {
        ++returnValue;
        if (returnValue > upperBound)
            returnValue = lowerBound;
    }
    else if (move == Down) {
        --returnValue;
        if (returnValue < lowerBound)
            returnValue = upperBound;
    }

    return returnValue;
}

ActionIndex Settings::exitRoutine(ActionIndex nextAction) {
    currentState = defaultScreen;
    currentOption = 0;
    return nextAction;
}

ActionIndex Settings::runStartLevel() {
    static int levelOption = utilsStartingLevel;
    lcd->displayTextAndNumber(levelFirstLine, levelOption);

    levelOption = getJoystickMove(1, noOfLevels, levelOption);

    if (joystick->pressedButton()) {
        utilsStartingLevel = levelOption;
        return exitRoutine(menuActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdContrast() {
    static int contrastOption = lcd->getContrast();
    lcd->displayTextAndNumber(lcdContrastFirstLine, contrastOption);

    contrastOption = getJoystickMove(lcdMinContrast, lcdMaxContrast, contrastOption);
    lcd->setContrast(contrastOption);

    if (joystick->pressedButton()) {
        return exitRoutine(menuActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdBrightness() {
    static int brightnessOption = lcd->getIntensity();
    lcd->displayTextAndNumber(lcdIntensityFirstLine, brightnessOption);

    brightnessOption = getJoystickMove(lcdMinIntensity, lcdMaxIntensity, brightnessOption);
    lcd->setIntensity(brightnessOption);

    if (joystick->pressedButton()) {
        return exitRoutine(menuActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runMatrixIntensity() {
    matrix->lightUp();

    static int matrixOption = matrix->getMatrixBrightness();
    lcd->displayTextAndNumber(matrixIntensityFirstLine, matrixOption);

    matrixOption = getJoystickMove(matrixMinIntensity, matrixMaxIntensity, matrixOption);
    matrix->setMatrixBrightness(matrixOption);

    if (joystick->pressedButton()) {
        matrix->lightDown();
        return exitRoutine(menuActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runDefaultScreen() {
    lcd->displayText(defaultFirstLine, options[currentOption]);

    if (joystick->pressedButton())
        currentState = SettingsState(currentOption);

    currentOption = getJoystickMove(0, noOfOptions - 1, currentOption);

    return settingsActionIndex;
}