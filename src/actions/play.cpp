#include "play.h"

void Play::initGame() {
    initGameState = true;

    levelId = utilsStartingLevel;
    // generate levels until the current one is reached 
    // start from 1
    for (int levelNo = 1; levelNo < levelId; ++levelNo) {
        level = level.getNewLevel();
    }

    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}

ActionIndex Play::run() {
    if (!initGameState)
        initGame();

    matrix->displayMap(currentView);

    if (currentGameState == dead) 
        return dieMario();
    else if (currentGameState == winning) 
        return winMario();

    displayPlayerData();
    return moveMario();
}

void Play::displayPlayerData() {
    lcd->displayGameInfo(levelId, time, score, lives);

    unsigned long now = millis();

    if (now - lastCountdown > countdownInterval) {
        lastCountdown = now;
        --time;
    }
}

ActionIndex Play::moveMario() {
    detectJump();
    Point nextMario = joystick->makeGameMove(mario);
    nextMario = applyGravity(nextMario);

    if (validPosition(nextMario)) {
        currentView.setPosition(mario, false);
        mario = changeCameraView(nextMario);
        currentView.setPosition(mario, true);      
    }
    else if (deadPosition(nextMario)) {
        if (--lives == 0)
            currentGameState = dead;

        resetGame(lives);
    }
    else if (winningPosition(nextMario)) {
        currentGameState = winning;
    }

    return playActionIndex;
}

bool Play::validPosition(Point nextMario) {
    // check new pos
    if (mario == nextMario)
        return false;

    // check bounds
    if (nextMario.x < 0 or nextMario.y < 0 or nextMario.x >= matrixSize or nextMario.y >= matrixSize)
        return false;

    // check if obstacle
    if (currentView.hasObstacle(nextMario))
        return false;

    // check if mario fell
    if (deadPosition(nextMario))
        return false;

    return true;
}

bool Play::deadPosition(Point marioPos) {
    return (marioPos.x == matrixSize - 1) and !currentView.hasObstacle(marioPos); // mario fell
}

bool Play::winningPosition(Point marioPos) {
    return (marioPos.y == 0) and level.reachedEndOfTheLevel();
}

Point Play::changeCameraView(Point marioPos) {
    if (marioPos.y < defaultMarioCol and level.hasNextColumn()) {
        currentView.appendColumn(level.getNextColumn());
        marioPos.y = defaultMarioCol;
    }
    else if (marioPos.y > defaultMarioCol and level.hasPrevColumn()) {
        currentView.prependColumn(level.getPrevColumn());
        marioPos.y = defaultMarioCol;
    }

    return marioPos;
}

Point Play::applyGravity(Point marioPos) {
    unsigned long now = millis();
    if (now - lastGravityChange > gravityChangeFreq) {
        lastGravityChange = now;

        Point nextMario = {marioPos.x + gravityDirection, marioPos.y};
        if (validPosition(nextMario) or deadPosition(nextMario)) 
            return nextMario;
    }

    return marioPos;
}

void Play::detectJump() {
    // jumping means inverting the direction of gravity
    unsigned long now = millis();

    if (now - lastJump > jumpInterval) {
        if (jumpingState == false and joystick->pressedButton()) {
            lastJump = now;
            gravityDirection = -1;
            jumpingState = true;
        }
        else if (jumpingState == true) {
            jumpingState = false;
            gravityDirection = 1;
        }
    }
}

ActionIndex Play::dieMario() {
    unsigned long now = millis();

    if (beginGameOverCountdown == 0)
        beginGameOverCountdown = now;

    if (now - beginGameOverCountdown < gameOverInterval) 
        lcd->displayText(gameOverLine1, gameOverLine2);
    else {
        lcd->displayTextAndNumber(scoreLine, score);
        if (joystick->pressedButton()) 
            return menuActionIndex;
    }

    return playActionIndex;
}

ActionIndex Play::winMario() {
    unsigned long now = millis();

    if (beginWinCountdown == 0)
        beginWinCountdown = now;

    if (now - beginWinCountdown < winInterval) 
        lcd->displayText(winLine1, winLine2);
    else {
        lcd->displayText(winNextLevelLine1, winNextLevelLine2);
        if (joystick->pressedButton()) 
            return advanceLevel();
    }

    return playActionIndex;
}

ActionIndex Play::advanceLevel() {
    return playActionIndex;
}

void Play::resetGame(int noLives) {
    if (noLives == 0) 
        noLives = maxLives;

    score = 0;
    time = maxTime;
    lives = noLives;

    lastJump = 0;
    jumpingState = false;

    mario = {defaultMarioRow, defaultMarioCol};
    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}