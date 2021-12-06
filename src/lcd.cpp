#include "../include/lcd.h"

Lcd::~Lcd() {
    delete lcd;
}

void Lcd::initSetup() {
    lcd->begin(lcdColumns, lcdRows);
}

void Lcd::displayText(char* msg1, char* msg2) {
    lcd->print(msg1);
    lcd->setCursor(0, 1);
    lcd->print(msg2);
}

void Lcd::clearText() {
    lcd->clear();
}