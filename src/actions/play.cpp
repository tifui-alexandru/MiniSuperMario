#include "play.h"

void Play::initGame() {
    initGameState = true;

    level.initLevel();

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
    bool changedMarioPos = false;
    Point nextMario = joystick->makeGameMove(mario);
    if (hitWall(nextMario))
        nextMario = mario;
    nextMario = applyGravity(nextMario);

    if (validPosition(nextMario)) {
        // move mario
        currentView.setPosition(mario, false);
        mario = changeCameraView(nextMario);
        currentView.setPosition(mario, true);
        
        // collect coin
        if (currentView.isCoin(mario)) {
            score += level.getCoinValue();
            level.eraseCoin(mario);
            currentView.eraseCoin(mario);
        }
    }
    else if (deadPosition(nextMario)) {
        if (--lives == 0)
            currentGameState = dead;
        resetGame();

    }
    else if (winningPosition(nextMario)) {
        currentGameState = winning;
        resetGame();
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

    // coins could be detected as obstacles
    // so check if obstacle and not coin
    if (currentView.isObstacle(nextMario) and !currentView.isCoin(nextMario))
        return false;

    // check if mario fell
    if (deadPosition(nextMario))
        return false;

    return true;
}

bool Play::hitWall(Point nextMario) {
    // check bounds
    if (nextMario.x < 0 or nextMario.y < 0 or nextMario.x >= matrixSize or nextMario.y >= matrixSize)
        return false;

    if (winningPosition(nextMario))
        return false;

    // coins could be detected as obstacles
    // so check if obstacle and not coin
    if (!currentView.isObstacle(nextMario) or currentView.isCoin(nextMario))
        return false;

    // check if mario fell
    if (deadPosition(nextMario))
        return false;

    return true;
}

bool Play::deadPosition(Point marioPos) {
    return (marioPos.x == matrixSize - 1) and (0 <= marioPos.y and marioPos.y < matrixSize) and !currentView.isObstacle(marioPos); // mario fell
}

bool Play::winningPosition(Point marioPos) {
    return (marioPos.y == 0) and level.reachedEndOfTheLevel();
}

Point Play::changeCameraView(Point marioPos) {
    if (marioPos.y < defaultMarioCol and level.hasNextColumn()) {
        byte nextMapCol = level.getNextColumn();
        byte nextCoinsCol = level.getNextCoinsColumn();
        level.moveCameraRight();

        currentView.appendColumn(nextMapCol, nextCoinsCol);
        marioPos.y = defaultMarioCol;
    }
    else if (marioPos.y > defaultMarioCol and level.hasPrevColumn()) {
        byte prevMapCol = level.getPrevColumn();
        byte prevCoinsCol = level.getPrevCoinsColumn();
        level.moveCameraLeft();

        currentView.prependColumn(prevMapCol, prevCoinsCol);
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

bool Play::marioIsOnGround() {
    Point underMario = {mario.x + 1, mario.y};

    // check bounds
    if (underMario.x < 0 or underMario.y < 0 or underMario.x >= matrixSize or underMario.y >= matrixSize)
        return false;

    // check if obstacle
    return currentView.isObstacle(underMario);
}

void Play::detectJump() {
    // jumping means inverting the direction of gravity
    unsigned long now = millis();

    if (now - lastJump > jumpInterval) {
        if (jumpingState == false and joystick->pressedButton() and marioIsOnGround()) {
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
        if (joystick->pressedButton()) {
            currentGameState = playing;
            
            return menuActionIndex;
        }
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
        if (joystick->pressedButton()) {
            return advanceLevel();
        }
    }

    return playActionIndex;
}

ActionIndex Play::advanceLevel() {
    if (levelId == noOfLevels) {
        lcd->displayText(finalLine1, finalLine2);
        if (joystick->pressedButton()) 
            return menuActionIndex;
    }
    else {
        currentGameState = playing;

        level = level.getNewLevel();
        currentView = level.getInitialView();
        currentView.setPosition(mario, true);

        return playActionIndex;
    }
}

void Play::resetGame() {
    jumpingState = false;
    mario = {defaultMarioRow, defaultMarioCol};
    score = lastScore;

    level.restartLevel();
    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}