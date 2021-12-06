#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class Lcd {
    const int RS = 13;
    const int enable = 9;
    const int D4 = 5;
    const int D5 = 4;
    const int D6 = 3;
    const int D7 = 2;

    LiquidCrystal* lcd = new LiquidCrystal(RS, enable, D4, D5, D6, D7);

    const int lcdRows = 2;
    const int lcdColumns = 16;

public:
    Lcd() {};
    ~Lcd();
    void initSetup();
    void displayText(char*, char*);
    void clearText();
};

#endif