#include "lcd.h"

Lcd::~Lcd() {
    delete lcd;
}

void Lcd::setContrast(byte newVal, EepromClass* eepromObj) {
    contrast = newVal;
    byte analogContrastValue = map(contrast, lcdMinContrast, lcdMaxContrast, contrastMinVisibleValue, contrastMaxVisibleValue);
    analogWrite(V0, analogContrastValue);
    eepromObj->writeLcdContrast(contrast);
}

void Lcd::setIntensity(byte newVal, EepromClass* eepromObj) {
    intensity = newVal;
    byte analogIntensityValue = map(intensity, lcdMinIntensity, lcdMaxIntensity, analogMinValue, analogMaxValue);
    analogWrite(A, analogIntensityValue);
    eepromObj->writeLcdIntensity(intensity);
}

void Lcd::initSetup(EepromClass *eepromObj) {
    lcd->createChar(heartId, heart);
    lcd->createChar(upDownId, upDown);
    lcd->createChar(okId, ok);

    pinMode(V0, OUTPUT);
    pinMode(A, OUTPUT);

    defaultContrast = eepromObj->readLcdContrast();
    defaultIntensity = eepromObj->readLcdIntensity();

    // reset to default values if not ok
    if (defaultContrast < lcdMinContrast or defaultIntensity > lcdMaxContrast)
        defaultContrast = (lcdMinContrast + lcdMaxContrast) / 2;

    if (defaultIntensity < lcdMinIntensity or defaultIntensity > lcdMaxIntensity)
        defaultIntensity = (lcdMinIntensity + lcdMaxIntensity) / 2;

    setContrast(defaultContrast, eepromObj);
    setIntensity(defaultIntensity, eepromObj);

    lcd->begin(lcdColumns, lcdRows);
}

void Lcd::displayText(char* msg1, char* msg2, bool upDownEmoji = false) {
    lastLayout = currentLayout;
    currentLayout = lcdLayout(msg1, msg2);

    if (currentLayout != lastLayout) {
        clearText();
        lcd->print(msg1);
        lcd->setCursor(0, 1);
        lcd->print(msg2);
    }

    if (upDownEmoji) {
        // set cursor on the firt row and last column and display UpDown emoji
        lcd->setCursor(lcdColumns - 1, 0);
        lcd->write(byte(upDownId));
    }
}

void Lcd::displayTextAndNumber(char* msg, int no, bool upDownEmoji = false) {
    char line[lcdColumns];
    for (byte i = 0; i < lcdColumns; ++i)
        line[i] = ' ';

    if (no == 0) 
        line[0] = '0';
    else {
        byte start = 0, stop = 0;

        while (no) {
            byte lastDigit = no % 10;
            no /= 10;

            line[stop] = char(lastDigit + '0');
            ++stop;
        }
        --stop;
        
        // reverse
        for (byte i = start, j = stop; i < j; ++i, --j) {
            char aux = line[i];
            line[i] = line[j];
            line[j] = aux;
        }
    }
       
    displayText(msg, line, upDownEmoji);
}

void Lcd::displayScrollingText(char* msg1, char* msg2, byte startPosMsg2, byte msg2Len) {
    char scrollingRow[lcdColumns];

    byte posMsg2 = startPosMsg2;

    for (byte i = 0; i < lcdColumns; ++i) {
        scrollingRow[i] = msg2[posMsg2];
        posMsg2 = (posMsg2 + 1) % msg2Len;
    }

    displayText(msg1, scrollingRow);
}

void Lcd::displayTextOnSecondLine(char* msg) {
    char firstLine[lcdColumns];
    for (byte i = 0; i < lcdColumns; ++i)
        firstLine[i] = currentLayout.layout[0][i];

    displayText(firstLine, msg);
}

void Lcd::lockPositionOnSecondLine(byte pos) {
    lcd->setCursor(pos, 1);
    lcd->blink();
}


void Lcd::unlockPositionOnSecondLine(byte pos) {
    lcd->setCursor(pos, 1);
    lcd->noBlink();
}

void Lcd::displayGameInfo(byte level, short time, int score, byte lives) {
    static byte lastLevel = 0;
    static byte lastTimeLen = 0;
    if (lastLevel != level or getIntegerLen(time) != lastTimeLen) {
        lastLevel = level;
        lastTimeLen = getIntegerLen(time);
        lcd->clear();
    }

    currentLayout = lcdLayout();
    lcd->home();

    lcd->print("Level ");
    lcd->print(level);
    lcd->print(" ");

    lcd->print("Time ");
    lcd->print(time);

    lcd->setCursor(0, 1);

    lcd->print("Score ");
    lcd->print(score);
    lcd->print(" ");

    byte scoreLen = getIntegerLen(score);
    for (byte i = 0; i < maxScoreLen - scoreLen; ++i)
        lcd->print(" ");

    lcd->print(lives);
    lcd->write(byte(heartId));

    lcd->home();
}

void Lcd::displayRegisterInfo(char* msg1, char* msg2) {
    if (currentLayout != lcdLayout(msg1, msg2)) {
        displayText(msg1, msg2);
        lcd->write(byte(okId));
    }
}

void Lcd::clearText() {
    lcd->clear();
}

byte Lcd::getIntegerLen(int no) {
    if (no == 0)
        return 1;

    byte ans = 0;

    while (no) {
        byte last_digit = no % 10;
        no /= 10;
        ++ans;
    }

    return ans;
}