#include "play.h"

ActionIndex Play::run() {
    lcd->displayText("PLAY", "GAME");
    matrix->displayMap(currentView);

    Point nextMario = joystick->makeGameMove(mario);
    moveMario(nextMario);

    return playActionIndex;
}

void Play::moveMario(Point nextMario) {
    if (validPosition(nextMario)) {
        Point newMario = changeCameraView(nextMario);
        currentView.setPosition(newMario, true);
        mario = newMario;
    }
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

Point Play::changeCameraView(Point nextMario) {
    currentView.setPosition(mario, false);

    if (nextMario.y < defaultMarioCol and level.hasNextColumn()) {
        currentView.appendColumn(level.getNextColumn());
        nextMario.y = defaultMarioCol;
    }
    else if (nextMario.y > defaultMarioCol and level.hasPrevColumn()) {
        currentView.prependColumn(level.getPrevColumn());
        nextMario.y = defaultMarioCol;
    }

    return nextMario;
}