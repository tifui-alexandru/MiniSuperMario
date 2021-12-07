#include "../include/about.h"

ActionIndex About::run() {
    unsigned long now = millis();
    if (now - lastCountTime > scrollInterval) {
        lastCountTime = now;
        startIndexFirstLine = (startIndexFirstLine + 1) % firstLineLength;
        startIndexSecondLine = (startIndexSecondLine + 1) % secondLineLength;
    }

    lcd->displayScrollingText(firstLine, secondLine, startIndexFirstLine, startIndexSecondLine);

    if (joystick->pressedButton()) 
        return menuActionIndex;
    
    return aboutActionIndex;
}