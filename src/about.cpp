#include "../include/about.h"

ActionIndex About::run() {
    unsigned long now = millis();
    if (now - lastCountTime > scrollInterval) {
        lastCountTime = now;
        startIndexSecondLine = (startIndexSecondLine + 1) % secondLineLength;
    }

    lcd->displayScrollingText(firstLine, secondLine, startIndexSecondLine, secondLineLength);

    if (joystick->pressedButton()) 
        return menuActionIndex;
    
    return aboutActionIndex;
}