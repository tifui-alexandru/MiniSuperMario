#include "wellcome.h"

ActionIndex Wellcome::run() {
    matrix->displayAnimation(wellcomeAnimation);

    unsigned long now = millis();
    if (now - startTime > interval) 
        return registerActionIndex;
    else {
        lcd->displayText("Welcome to", "Mini Super Mario!");
        return wellcomeActionIndex;
    }
}