#include "../include/wellcome.h"

ActionIndex Wellcome::run() {
    unsigned long now = millis();
    if (now - startTime > interval) 
        return menuActionIndex;
    else {
        lcd->displayText(msgLine1, msgLine2);
        return wellcomeActionIndex;
    }
}

// void Wellcome::initSetup() {
//     Serial.println("*******************");
//     startTime = millis();
// }