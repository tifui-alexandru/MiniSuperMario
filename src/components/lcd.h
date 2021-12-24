#ifndef LCD_H
#define LCD_H

/*
    Manipulates the LCD.
*/

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "utils.h"
#include "eeprom.h"

class Lcd {
    const byte RS = 13;
    const byte enable = 9;
    const byte D4 = 7;
    const byte D5 = A5;
    const byte D6 = 4;
    const byte D7 = 2;
    const byte V0 = 5;
    const byte A = 6;

    LiquidCrystal* lcd = new LiquidCrystal(RS, enable, D4, D5, D6, D7);

    static const byte lcdRows = 2;
    static const byte lcdColumns = 16;

    struct lcdLayout {
        char layout[lcdRows][lcdColumns];

        lcdLayout() {
            for (byte row = 0; row < lcdRows; ++row)
                for (byte col = 0; col < lcdColumns; ++col)
                    layout[row][col] = 0;
        }

        lcdLayout(const char* row1, const char* row2) {
            for (byte col = 0; col < lcdColumns; ++col)
                layout[0][col] = layout[1][col] = 0;

            for (byte col = 0; row1[col] and col < lcdColumns; ++col)
                layout[0][col] = row1[col];

            for (byte col = 0; row2[col] and col < lcdColumns; ++col)
                layout[1][col] = row2[col];
        }

        bool operator == (const lcdLayout& other) const {
            for (byte row = 0; row < lcdRows; ++row)
                for (byte col = 0; col < lcdColumns; ++col)
                    if (layout[row][col] != other.layout[row][col])
                        return false;
            return true;
        }

        bool operator != (const lcdLayout& other) const {
            return !(*this == other);
        }

        lcdLayout operator = (const lcdLayout& other) {
            for (byte row = 0; row < lcdRows; ++row)
                for (byte col = 0; col < lcdColumns; ++col)
                    layout[row][col] = other.layout[row][col];
            return *this;
        }
    };

    lcdLayout currentLayout;
    lcdLayout lastLayout;

    byte defaultContrast = 5;
    byte defaultIntensity = 8;

    byte contrast;
    byte intensity;

    unsigned long lastBlink = 0;
    const unsigned long blinkingInterval = 200;
    bool blinkingState = false;

    const byte maxScoreLen = 6;
    
    static const byte emojiSize = 8;

    byte heart[emojiSize] = {
        B01010,
        B11111,
        B11111,
        B01110,
        B01110,
        B00100,
        B00000
    };
    byte heartId = 0;

    byte upDown[emojiSize] = {
        B00100,
        B01110,
        B11111,
        B00000,
        B11111,
        B01110,
        B00100
    };
    byte upDownId = 1;

    byte ok[emojiSize] = {
        B00000,
        B00000,
        B00000,
        B00001,
        B10010,
        B10100,
        B01000
    };
    byte okId = 2;

    byte getIntegerLen(int);

public:
    Lcd() {};
    ~Lcd();

    byte getContrast() { return contrast; }
    byte getIntensity() { return intensity; }

    void setContrast(byte, EepromClass*);
    void setIntensity(byte, EepromClass*);

    void initSetup(EepromClass*);

    void displayText(char*, char*, bool upDownEmoji = false);
    void displayTextAndNumber(char*, int, bool upDownEmoji = false);

    void displayGameInfo(byte, short, int, byte);
    void displayRegisterInfo(char*, char*);

    void displayScrollingText(char*, char*, byte, byte);
    void displayTextOnSecondLine(char*);

    void lockPositionOnSecondLine(byte);
    void unlockPositionOnSecondLine(byte);

    void clearText();
};

#endif