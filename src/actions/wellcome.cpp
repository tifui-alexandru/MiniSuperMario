#include "wellcome.h"

ActionIndex Wellcome::run() {
    unsigned long now = millis();
    if (now - startTime > interval) 
        return registerActionIndex;
    else {
        lcd->displayText(msgLine1, msgLine2);
        return wellcomeActionIndex;
    }
}