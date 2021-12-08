#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include "action.h"

class Settings : public Action {
    char* defaultFirstLine = "Settings options: "; // to do: add up and down emoji

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

    byte currentOption;
    SettingsState currentState = defaultScreen;

    void updateOption();

    ActionIndex runStartLevel();
    ActionIndex runLcdContrast();
    ActionIndex runLcdBrightness();
    ActionIndex runMatrixIntensity();
    ActionIndex runChangeNickname();
    ActionIndex runBackToMenu();
    ActionIndex runDefaultScreen();

public:
    Settings(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif