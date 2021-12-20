#include "lcd.h"

Lcd::~Lcd() {
    delete lcd;
}

void Lcd::setContrast(byte newVal) {
    contrast = newVal;
    // byte analogContrastValue = map(contrast, lcdMinContrast, lcdMaxContrast, analogMinValue, analogMaxValue);
    // analogWrite(V0, analogContrastValue);
}

void Lcd::setIntensity(byte newVal) {
    intensity = newVal;
    byte analogIntensityValue = map(intensity, lcdMinIntensity, lcdMaxIntensity, analogMinValue, analogMaxValue);
    analogWrite(A, analogIntensityValue);
}

void Lcd::initSetup() {
    // pinMode(V0, OUTPUT);
    pinMode(A, OUTPUT);

    // setContrast(defaultContrast);
    setIntensity(defaultIntensity);

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

void Lcd::displayTextAndNumber(char* msg, int no) {
    char line[lcdColumns];
    for (int i = 0; i < lcdColumns; ++i)
        line[i] = ' ';

    if (no == 0) 
        line[0] = '0';
    else {
        int start = 0, stop = 0;

        while (no) {
            int lastDigit = no % 10;
            no /= 10;

            line[stop] = char(lastDigit + '0');
            ++stop;
        }
        --stop;
        
        // reverse
        for (int i = start, j = stop; i < j; ++i, --j) {
            char aux = line[i];
            line[i] = line[j];
            line[j] = aux;
        }
    }
       
    displayText(msg, line);
}

void Lcd::displayScrollingText(char* msg1, char* msg2, int startPosMsg2, int msg2Len) {
    char scrollingRow[lcdColumns];

    int posMsg2 = startPosMsg2;

    for (int i = 0; i < lcdColumns; ++i) {
        scrollingRow[i] = msg2[posMsg2];
        posMsg2 = (posMsg2 + 1) % msg2Len;
    }

    displayText(msg1, scrollingRow);
}

void Lcd::displayTextOnSecondLine(char* msg) {
    char firstLine[lcdColumns];
    for (int i = 0; i < lcdColumns; ++i)
        firstLine[i] = currentLayout.layout[0][i];

    displayText(firstLine, msg);
}

void Lcd::lockPositionOnSecondLine(int pos) {
    lcd->setCursor(pos, 1);
    lcd->blink();
}


void Lcd::unlockPositionOnSecondLine(int pos) {
    lcd->setCursor(pos, 1);
    lcd->noBlink();
}

void Lcd::displayGameInfo(int level, int time, int score, int lives) {
    static int lastLevel = 0;
    if (lastLevel != level) {
        lastLevel = level;
        lcd->clear();
    }

    currentLayout = lcdLayout();
    lcd->home();

    lcd->print("Level ");
    lcd->print(level);
    lcd->print(" ");

    lcd->print("Time ");
    lcd->print(time);
    lcd->print(time);

    lcd->setCursor(0, 1);

    lcd->print("Score ");
    lcd->print(score);
    lcd->print(" ");

    int scoreLen = getIntegerLen(score);
    for (int i = 0; i < maxScoreLen - scoreLen; ++i)
        lcd->print(" ");

    lcd->print(lives);
    lcd->write(byte(heartId));

    lcd->home();
}

void Lcd::clearText() {
    lcd->clear();
}

int Lcd::getIntegerLen(int no) {
    if (no == 0)
        return 1;

    int ans = 0;

    while (no) {
        int last_digit = no % 10;
        no /= 10;
        ++ans;
    }

    return ans;
}