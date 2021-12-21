#include "wellcome.h"

ActionIndex Wellcome::run() {
    unsigned long now = millis();
    if (now - startTime > interval) 
        return registerActionIndex;
    else {
        lcd->displayText("Welcome to", "Mini Super Mario!");
        return wellcomeActionIndex;
    }
}