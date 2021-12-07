#include "play.h"

void Play::moveMario(Point newMario) {
    if (mario != newMario) {
        Serial.print(newMario.x);
        Serial.print(" ");
        Serial.println(newMario.y);
        currentView.setPosition(mario, false);
        currentView.setPosition(newMario, true);
        mario = newMario;
    }
}

ActionIndex Play::run() {
    lcd->displayText("PLAY", "GAME");
    matrix->displayMap(currentView);

    Point nextMario = joystick->makeGameMove(mario);
    moveMario(nextMario);

    return playActionIndex;
}