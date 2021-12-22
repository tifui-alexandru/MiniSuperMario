#include "settings.h"

ActionIndex Settings::run() {
    matrix->displaySettingAnimation();

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
    else if (currentState == musicOnOff)
        return runMusicOnOff();
    else if (currentState == backToMenu)
        return exitRoutine(menuActionIndex);
    else
        return runDefaultScreen();
}

byte Settings::getJoystickMove(byte lowerBound, byte upperBound, byte value) {
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
    return nextAction;
}

ActionIndex Settings::runMusicOnOff() {
    musicState = !musicState;

    if (musicState)
        options[(int)musicOnOff] = "Turn music OFF";
    else
        options[(int)musicOnOff] = "Turn music ON";

    return exitRoutine(settingsActionIndex);
}

ActionIndex Settings::runStartLevel() {
    static int levelOption = utilsStartingLevel;
    lcd->displayTextAndNumber("Select level no", levelOption);

    levelOption = getJoystickMove(1, noOfLevels, levelOption);

    if (joystick->pressedButton()) {
        utilsStartingLevel = levelOption;
        Serial.println("*****");
        Serial.println(utilsStartingLevel);
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdContrast() {
    static int contrastOption = lcd->getContrast();
    lcd->displayTextAndNumber("LCD contrast", contrastOption);

    contrastOption = getJoystickMove(lcdMinContrast, lcdMaxContrast, contrastOption);
    lcd->setContrast(contrastOption, eepromObj);

    if (joystick->pressedButton()) {
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdBrightness() {
    static int brightnessOption = lcd->getIntensity();
    lcd->displayTextAndNumber("LCD brightness", brightnessOption);

    brightnessOption = getJoystickMove(lcdMinIntensity, lcdMaxIntensity, brightnessOption);
    lcd->setIntensity(brightnessOption, eepromObj);

    if (joystick->pressedButton()) {
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runMatrixIntensity() {
    matrix->lightUp();

    static int matrixOption = matrix->getMatrixBrightness();
    lcd->displayTextAndNumber("Matrix intensity", matrixOption);

    matrixOption = getJoystickMove(matrixMinIntensity, matrixMaxIntensity, matrixOption);
    matrix->setMatrixBrightness(matrixOption, eepromObj);

    if (joystick->pressedButton()) {
        matrix->lightDown();
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runDefaultScreen() {
    lcd->displayText("Settings options ", options[currentOption]);

    if (joystick->pressedButton())
        currentState = SettingsState(currentOption);

    currentOption = getJoystickMove(0, noOfOptions - 1, currentOption);

    return settingsActionIndex;
}