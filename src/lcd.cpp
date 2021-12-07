#include "../include/lcd.h"

Lcd::~Lcd() {
    delete lcd;
}

void Lcd::initSetup() {
    lcd->begin(lcdColumns, lcdRows);
}

void Lcd::displayText(char* msg1, char* msg2) {
    lastLayout = currentLayout;
    currentLayout = lcdLayout(msg1, msg2);

    if (currentLayout != lastLayout) {
        clearText();
        lcd->print(msg1);
        lcd->setCursor(0, 1);
        lcd->print(msg2);
    }
}

void Lcd::displayScrollingText(char* msg1, char* msg2, int startPosMsg1, int startPosMsg2) {
    char row1[lcdColumns];
    char row2[lcdColumns];

    int posMsg1 = startPosMsg1;
    int posMsg2 = startPosMsg2;

    for (int i = 0; i < lcdColumns; ++i) {
        row1[i] = msg1[posMsg1];
        row2[i] = msg2[posMsg2];

        posMsg1 = (posMsg1 + 1) % lcdColumns;
        posMsg2 = (posMsg2 + 1) % lcdColumns;
    }

    displayText(row1, row2);
}

void Lcd::clearText() {
    lcd->clear();
}