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
    int levelId;

    Level level;
    Point mario = {defaultMarioRow, defaultMarioCol};
    CameraView currentView;

    char* gameOverLine1 = "GAME";
    char* gameOverLine2 = "OVER";

    char* winLine1 = "CONGRATULATIONS!";
    char* winLine2 = "YOU WON";

    const unsigned long countdownInterval = 1000;
    unsigned long lastCountdown = 0;

    const unsigned long jumpInterval = 410;
    unsigned long lastJump = 0;

    const unsigned long gravityChangeFreq = 100;
    unsigned long lastGravityChange = 0;
    int gravityDirection = 1;

    bool initGameState = false;
    void initGame();

    ActionIndex moveMario();

    bool validPosition(Point);
    bool deadPosition(Point);
    bool winningPosition(Point);

    Point changeCameraView(Point);
    Point applyGravity(Point);

    bool jumpingState = false;
    void detectJump();

    ActionIndex dieMario();
    ActionIndex winMario();

    enum GameState {
        playing,
        dead,
        winning
    };
    GameState currentGameState = playing;

    void displayPlayerData();

    void resetGameState(int);

public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif