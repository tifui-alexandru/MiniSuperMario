#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include "action.h"

class Settings : public Action {
    char* defaultFirstLine = "Settings options "; // to do: add up and down emoji
    char* levelFirstLine = "Select level no";
    char* lcdContrastFirstLine = "LCD contrast";
    char* lcdIntensityFirstLine = "LCD brightness";
    char* matrixIntensityFirstLine = "Matrix intensity";

    static const byte noOfOptions = 6;
    char* options[noOfOptions] = {
        "Start level",
        "LCD contrast",
        "LCD brightness",
        "Matrix intensity",
        "Change nickname",
        "Back to menu"
    };

    enum SettingsState {
        startLevel,
        lcdContrast,
        lcdBrightness,
        matrixIntensity,
        changeNickname,
        backToMenu,
        defaultScreen
    };

    byte currentOption = 0;
    SettingsState currentState = defaultScreen;

    int getJoystickMove(int, int, int);
    ActionIndex exitRoutine(ActionIndex);

    ActionIndex runStartLevel();
    ActionIndex runLcdContrast();
    ActionIndex runLcdBrightness();
    ActionIndex runMatrixIntensity();
    ActionIndex runDefaultScreen();

public:
    Settings(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif