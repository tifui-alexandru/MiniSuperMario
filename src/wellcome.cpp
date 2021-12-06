#include "../include/wellcome.h"

ActionIndex Wellcome::run() {
    if (millis() - startTime > interval) 
        return menuActionIndex;
}

Wellcome::Wellcome() {
    startTime = millis();
    lcd->displayText(msgLine1, msgLine2);
}