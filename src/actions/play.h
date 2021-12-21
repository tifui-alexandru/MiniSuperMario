#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"
#include "../game/level.h"

class Play : public Action {
    const byte maxLives = 3;
    const short maxTime = 999; // in seconds
    const byte noOfLevels = 5;
    const byte defaultMarioRow = 6;
    const byte defaultMarioCol = 5;

    byte lives = maxLives;
    int score = 0;
    int lastScore = 0;
    short totalLevelTime = maxTime;
    short time = maxTime;
    byte levelId;

    Level level;
    Point mario = {defaultMarioRow, defaultMarioCol};
    CameraView currentView;

    const unsigned long winInterval = 2000;
    unsigned long beginWinCountdown = 0;

    const unsigned long gameOverInterval = 2000;
    unsigned long beginGameOverCountdown = 0;

    const unsigned long countdownInterval = 1000;
    unsigned long lastCountdown = 0;

    const unsigned long jumpInterval = 430;
    unsigned long lastJump = 0;

    const unsigned long gravityChangeFreq = 100;
    unsigned long lastGravityChange = 0;
    byte gravityDirection = 1;

    bool initGameState = false;
    void initGame();

    ActionIndex moveMario();

    bool hitWall(Point);
    bool validPosition(Point);
    bool deadPosition(Point);
    bool winningPosition(Point);

    Point changeCameraView(Point);
    Point applyGravity(Point);

    bool jumpingState = false;
    void detectJump();
    bool marioIsOnGround();

    ActionIndex dieMario();
    ActionIndex winMario();
    ActionIndex advanceLevel();

    enum GameState {
        playing,
        dead,
        winning
    };
    GameState currentGameState = playing;

    void displayPlayerData();

    void resetGame();

public:
    Play(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};
        
    ActionIndex run() override;
};

#endif