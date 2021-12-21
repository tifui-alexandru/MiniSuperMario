#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include "action.h"

class Settings : public Action {
    static const byte noOfOptions = 7;
    char* options[noOfOptions] = {
        "Start level",
        "LCD contrast",
        "LCD brightness",
        "Matrix intensity",
        "Change nickname",
        "Turn music OFF",
        "Back to menu"
    };
    
    enum SettingsState {
        startLevel,
        lcdContrast,
        lcdBrightness,
        matrixIntensity,
        changeNickname,
        musicOnOff,
        backToMenu,
        defaultScreen
    };

    byte currentOption = 0;
    SettingsState currentState = defaultScreen;

    byte getJoystickMove(byte, byte, byte);
    ActionIndex exitRoutine(ActionIndex);

    ActionIndex runStartLevel();
    ActionIndex runLcdContrast();
    ActionIndex runLcdBrightness();
    ActionIndex runMatrixIntensity();
    ActionIndex runMusicOnOff();
    ActionIndex runDefaultScreen();

public:
    Settings(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif