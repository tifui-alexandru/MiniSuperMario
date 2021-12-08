#ifndef REGISTER_H
#define REGISTER_H

#include "action.h"

class Register : public Action {
    char* firstLine = "Choose nickname";
    char* nicknameLine = "    aaaaaaK     "; // last char should be an ok emoji

    // the available characters are from 'a' to 'z' and ' '

    const int nicknameLen = 6;
    const int nicknameStartPos = 4;
    const int nicknameEndPos = nicknameStartPos + nicknameLen;

    int currentLetterIndex = nicknameStartPos;

    enum RegisterState {
        selectLetterIndex,
        changeLetter
    };

    char getNextLetter(char);
    char getPrevLetter(char);

    RegisterState state = selectLetterIndex;

    ActionIndex runSelectLetterIndex();
    ActionIndex runChangeLetter();

public :
    Register(Lcd *lcd = nullptr, Joystick *joystick = nullptr, Matrix *matrix = nullptr, Buzzer *buzzer = nullptr, EepromClass *eepromObj = nullptr) : 
        Action(lcd, joystick, matrix, buzzer, eepromObj) {};

    ActionIndex run() override;
};

#endif