#include "play.h"

ActionIndex Play::run() {
    lcd->displayText("PLAY", "GAME");
    matrix->displayMap(currentView);
    Point nextMario = jumpMario(joystick->makeGameMove(mario));
    return moveMario(nextMario);
}

ActionIndex Play::moveMario(Point nextMario) {
    if (validPosition(nextMario)) {
        currentView.setPosition(mario, false);

        Point newMario = changeCameraView(applyGravity(nextMario));
        mario = newMario;
        
        currentView.setPosition(mario, true);

        if (deadPosition()) 
            return dieMario();        
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

    return true;
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
    if (jumpingState)
        return marioPos;

    while (validPosition({marioPos.x + 1, marioPos.y}))
        ++marioPos.x;
    return marioPos;
}

Point Play::jumpMario(Point marioPos) {
    // detect jump
    unsigned long now = millis();
    if (joystick->pressedButton() and now - lastJump > jumpInterval) {
        lastJump = now;
        jumpingState = true;
        jumpModifyRate = -1; // enter ascending part of the jump
    }
    
    if (jumpingState == true) {
        if (now - lastJump > jumpInterval) 
            jumpingState = false;
        else {
            // perform jump
            if (now - lastJumpModification > jumpModifyFreq) {
                lastJumpModification = now;
                marioPos.x += jumpModifyRate;
            }

            if (now - lastJump > jumpInterval / 2) 
                jumpModifyRate = 1; // enter descending part of the jump
        }
    }

    return marioPos;
}

bool Play::deadPosition() {
    return mario.x == matrixSize - 1; // mario fell
}

ActionIndex Play::dieMario() {
    ActionIndex returnValue = playActionIndex;

    if (--lives == 0) {
        // game over code
        lcd->displayText(gameOverLine1, gameOverLine2);
        returnValue = menuActionIndex;
        delay(5000);
    }

    resetGameState(lives);
    return returnValue;
}

void Play::resetGameState(int noLives) {
    if (noLives == 0) 
        noLives = maxLives;

    score = 0;
    time = maxTime;
    lives = noLives;

    jumpingState = false;
    lastJump = 0;
    lastJumpModification = 0;

    mario = {defaultMarioRow, defaultMarioCol};
    currentView = level.getInitialView();
    currentView.setPosition(mario, true);
}