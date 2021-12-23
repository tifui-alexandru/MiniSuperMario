#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include "action.h"

class Settings : public Action {
    const byte settingsAnimation[matrixSize] = {
        B00011000,
        B00111100,
        B01000010,
        B11011011,
        B11011011,
        B01000010,
        B00111100,
        B00011000
    };

    static const byte noOfOptions = 8;
    char* options[noOfOptions] = {
        "Start level",
        "LCD contrast",
        "LCD brightness",
        "Matrix intensity",
        "Change nickname",
        "Turn sounds OFF",
        "Reset scoreboard",
        "Back to menu"
    };
    
    enum SettingsState {
        startLevel,
        lcdContrast,
        lcdBrightness,
        matrixIntensity,
        changeNickname,
        soundsOnOff,
        resetScoreboard,
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
    ActionIndex runsoundsOnOff();
    ActionIndex runResetScoreboard();
    ActionIndex runDefaultScreen();

public:
    Settings(Lcd* lcd = nullptr, Joystick* joystick = nullptr, Matrix* matrix = nullptr, 
        Buzzer* buzzer = nullptr, EepromClass* eepromObj = nullptr, Utils* gameUtils = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj, gameUtils) {}
        
    virtual ~Settings() {}

    ActionIndex run() override;
};

#endif