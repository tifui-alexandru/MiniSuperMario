#include "settings.h"

ActionIndex Settings::run() {
    matrix->displayAnimation(settingsAnimation);

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
    else if (currentState == resetScoreboard)
        return runResetScoreboard();
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
    gameUtils->musicState = !gameUtils->musicState;

    if (gameUtils->musicState)
        options[(int)musicOnOff] = "Turn music OFF";
    else
        options[(int)musicOnOff] = "Turn music ON";

    return exitRoutine(settingsActionIndex);
}

ActionIndex Settings::runResetScoreboard() {
    // ask the user if they are sure
    // 0 for no, 1 for yes
    static const int yes = 1;
    static const int no = 0;
    static int resetOption = no;

    resetOption = getJoystickMove(no, yes, resetOption);

    if (resetOption == no)
        lcd->displayText("Are you sure?", "NO", true);
    else
        lcd->displayText("Are you sure?", "YES", true);

    if (joystick->pressedButton()) {
        if (resetOption == yes)
            eepromObj->resetScoreboard();
            
        return exitRoutine(settingsActionIndex);
    }
}

ActionIndex Settings::runStartLevel() {
    static int levelOption = gameUtils->utilsStartingLevel;
    lcd->displayTextAndNumber("Select level no", levelOption, true);

    levelOption = getJoystickMove(1, noOfLevels, levelOption);

    if (joystick->pressedButton()) {
        gameUtils->utilsStartingLevel = levelOption;
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdContrast() {
    static int contrastOption = lcd->getContrast();
    lcd->displayTextAndNumber("LCD contrast", contrastOption, true);

    contrastOption = getJoystickMove(lcdMinContrast, lcdMaxContrast, contrastOption);
    lcd->setContrast(contrastOption, eepromObj);

    if (joystick->pressedButton()) {
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runLcdBrightness() {
    static int brightnessOption = lcd->getIntensity();
    lcd->displayTextAndNumber("LCD brightness", brightnessOption, true);

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
    lcd->displayTextAndNumber("Matrix intensity", matrixOption, true);

    matrixOption = getJoystickMove(matrixMinIntensity, matrixMaxIntensity, matrixOption);
    matrix->setMatrixBrightness(matrixOption, eepromObj);

    if (joystick->pressedButton()) {
        matrix->lightDown();
        return exitRoutine(settingsActionIndex);
    }

    return settingsActionIndex;
}

ActionIndex Settings::runDefaultScreen() {
    lcd->displayText("Settings menu", options[currentOption], true);

    if (joystick->pressedButton())
        currentState = SettingsState(currentOption);

    currentOption = getJoystickMove(0, noOfOptions - 1, currentOption);

    return settingsActionIndex;
}