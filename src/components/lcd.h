#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "../../include/utils.h"

class Lcd {
    const int RS = 13;
    const int enable = 9;
    const int D4 = 7;
    const int D5 = 5;
    const int D6 = 4;
    const int D7 = 2;
    // const int V0 = 3;
    const int A = 3;

    LiquidCrystal* lcd = new LiquidCrystal(RS, enable, D4, D5, D6, D7);

    static const int lcdRows = 2;
    static const int lcdColumns = 16;

    struct lcdLayout {
        char layout[lcdRows][lcdColumns];

        lcdLayout() {
            for (int row = 0; row < lcdRows; ++row)
                for (int col = 0; col < lcdColumns; ++col)
                    layout[row][col] = 0;
        }

        lcdLayout(const char* row1, const char* row2) {
            for (int col = 0; col < lcdColumns; ++col) 
                layout[0][col] = layout[1][col] = 0;

            for (int col = 0; row1[col] and col < lcdColumns; ++col)
                layout[0][col] = row1[col];

            for (int col = 0; row2[col] and col < lcdColumns; ++col)
                layout[1][col] = row2[col];
        }

        bool operator == (const lcdLayout& other) const {
            for (int row = 0; row < lcdRows; ++row) 
                for (int col = 0; col < lcdColumns; ++col) 
                    if (layout[row][col] != other.layout[row][col])
                        return false;
            return true;
        }

        bool operator != (const lcdLayout& other) const {
            return !(*this == other);
        }

        lcdLayout operator = (const lcdLayout& other) {
            for (int row = 0; row < lcdRows; ++row)
                for (int col = 0; col < lcdColumns; ++col) 
                    layout[row][col] = other.layout[row][col];
            return *this;
        }
    };

    lcdLayout currentLayout;
    lcdLayout lastLayout;

    const byte defaultContrast = 5;
    const byte defaultIntensity = 8;

    byte contrast;
    byte intensity;

    unsigned long lastBlink = 0;
    const unsigned long blinkingInterval = 200;
    bool blinkingState = false;

    const byte maxScoreLen = 6;

    byte heart[8] = {
        B01010,
        B11111,
        B11111,
        B01110,
        B01110,
        B00100,
        B00000,
    };
    byte heartId = 0;

    int getIntegerLen(int);
    char* convertIntegerToString(int);

public:
    Lcd() {
        lcd->createChar(heartId, heart);
    };
    ~Lcd();

    byte getContrast() { return contrast; }
    byte getIntensity() { return intensity; }

    void setContrast(byte);
    void setIntensity(byte);

    void initSetup();

    void displayText(char*, char*);
    void displayTextAndNumber(char*, int);

    void displayGameInfo(int, int, int, int);

    void displayScrollingText(char*, char*, int, int);
    void displayTextOnSecondLine(char*);

    void lockPositionOnSecondLine(int);
    void unlockPositionOnSecondLine(int);

    void clearText();
};

#endif