#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"
#include "../game/level.h"

class Play : public Action {
    const int maxLives = 3;
    const int maxTime = 1000; // in seconds
    const int noOfLevels = 5;
    const int defaultMarioRow = 6;
    const int defaultMarioCol = 5;

    int lives = maxLives;
    int score = 0;
    int time = maxTime;

    Level level;
    Point mario = {defaultMarioRow, defaultMarioCol};
    CameraView currentView;

    char* gameOverLine1 = "GAME";
    char* gameOverLine2 = "OVER";

    const unsigned long jumpInterval = 800;
    const unsigned long jumpModifyFreq = 100;

    unsigned long lastJump = 0;
    unsigned long lastJumpModification = 0;

    int jumpModifyRate;
    bool jumpingState = false;

    ActionIndex moveMario(Point);
    bool validPosition(Point);

    Point changeCameraView(Point);
    Point applyGravity(Point);
    Point jumpMario(Point);

    bool deadPosition();
    ActionIndex dieMario();

    void resetGameState(int);

public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {
            currentView = level.getInitialView();
            currentView.setPosition(mario, true);
        };
        
    ActionIndex run() override;
};

#endif