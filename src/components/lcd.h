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

    unsigned long lastBlink = 0;
    const unsigned long blinkingInterval = 200;
    bool blinkingState = false;

public:
    Lcd() {};
    ~Lcd();

    void initSetup();

    void displayText(char*, char*);
    void displayScrollingText(char*, char*, int, int);

    void displayTextOnSecondLine(char*);
    void displayNumberOnSecondLine(int);

    void lockPositionOnSecondLine(int);
    void unlockPositionOnSecondLine(int);

    void clearText();
};

#endif