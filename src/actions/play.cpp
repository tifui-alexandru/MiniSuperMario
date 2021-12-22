#include "play.h"

void Play::initGame() {
    initGameState = true;

    if (levelId == 1)
        level.initLevel();

    levelId = utilsStartingLevel;
    // generate levels until the current one is reached 
    // start from 1
    for (byte levelNo = 1; levelNo < levelId; ++levelNo)
        level.advanceToNextLevel();

    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}

ActionIndex Play::run() {
    if (!initGameState)
        initGame();

    // if game is finished
    if (levelId > noOfLevels) {
        lcd->displayText("CONGRATULATIONS!", "GAME FINISHED");
        if (joystick->pressedButton()) {
            initGameState = false;
            return menuActionIndex;
        }
        return playActionIndex;
    }

    if (currentGameState == dead) 
        return dieMario();
    else if (currentGameState == winning) 
        return winMario();

    matrix->displayMap(currentView);

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
    matrix->displaySadAnimation();

    unsigned long now = millis();

    if (beginGameOverCountdown == 0)
        beginGameOverCountdown = now;

    bool enteredTop3 = eepromObj->write(playerNickname, score);

    if (now - beginGameOverCountdown < gameOverInterval) {
        if (enteredTop3)
            lcd->displayText(playerNickname, "You are in top 3");
        else
            lcd->displayText(playerNickname, "GAME OVER");
    }
    else {
        lcd->displayTextAndNumber("Score:     PRESS", score);


        if (joystick->pressedButton()) {
            currentGameState = playing;
            beginGameOverCountdown = 0;
            resetGame();

            return menuActionIndex;
        }
    }

    return playActionIndex;
}

ActionIndex Play::winMario() {
    matrix->displayHappyAnimation();
    unsigned long now = millis();

    if (beginWinCountdown == 0)
        beginWinCountdown = now;

    if (now - beginWinCountdown < winInterval) 
        lcd->displayText("Congrats,", playerNickname);
    else {
        lcd->displayText("Press the button", "to advance level");
        if (joystick->pressedButton()) {
            beginWinCountdown = 0;
            return advanceLevel();
        }
    }

    return playActionIndex;
}

ActionIndex Play::advanceLevel() {
    ++levelId;
    score += (totalLevelTime - time);

    if (levelId <= noOfLevels) {
        currentGameState = playing;

        level.advanceToNextLevel();

        jumpingState = false;
        gravityDirection = 1;
        mario = {defaultMarioRow, defaultMarioCol};
        currentView = level.getInitialView();
        currentView.setPosition(mario, true);

        time = totalLevelTime = level.getTime();
        lastScore = score;
    }
    return playActionIndex;
}

void Play::resetGame() {
    jumpingState = false;
    gravityDirection = 1;
    mario = {defaultMarioRow, defaultMarioCol};
    score = lastScore;

    initGameState = false;

    level.restartLevel();
    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}