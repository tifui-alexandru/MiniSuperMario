#include "about.h"

ActionIndex About::run() {
    matrix->displayAnimation(infoAnimation);

    unsigned long now = millis();
    if (now - lastCountTime > scrollInterval) {
        lastCountTime = now;
        startIndexSecondLine = (startIndexSecondLine + 1) % secondLineLength;
    }

    lcd->displayScrollingText("Mini Super Mario", " Creator: Alexandru Tifui source code: https://github.com/tifui-alexandru/MiniSuperMario ", \
                                startIndexSecondLine, secondLineLength);

    if (joystick->pressedButton()) {
        buzzer->beep();
        return menuActionIndex;
    }
    
    return aboutActionIndex;
}