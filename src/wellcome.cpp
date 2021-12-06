#include "../include/wellcome.h"

ActionIndex Wellcome::run() {
    Serial.println("***");
    Serial.print("start: ");
    Serial.println(startTime);

    Serial.print("now: ");
    Serial.println(millis());

    Serial.print("diff: ");
    Serial.println(millis() - startTime);

    if (millis() - startTime > interval)
        return menuActionIndex;
    else {
        lcd->displayText(msgLine1, msgLine2);
        return wellcomeActionIndex;
    }
}

void Wellcome::initSetup() {
    startTime = millis();
}