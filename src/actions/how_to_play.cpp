#include "how_to_play.h"

ActionIndex HowToPlay::run() {
    matrix->displayAnimation(questionAnimation);

    if (joystick->pressedButton()) {
        buzzer->beep();
        return menuActionIndex;
    }

     unsigned long now = millis();
    if (now - lastCountTime > scrollInterval) {
        lastCountTime = now;
        startIndexSecondLine = (startIndexSecondLine + 1) % secondLineLength;
    }

    lcd->displayScrollingText("Instructions at:", " https://github.com/tifui-alexandru/MiniSuperMario ", \
                                startIndexSecondLine, secondLineLength);

    return howToPlayActionIndex;
}