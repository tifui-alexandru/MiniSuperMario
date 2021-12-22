#include "register.h"

ActionIndex Register::run() {
    lcd->displayRegisterInfo(" Enter nickname", nicknameLine);

    if (state == selectLetterIndex)
        return runSelectLetterIndex();
    else
        return runChangeLetter();
}

ActionIndex Register::runSelectLetterIndex() {
    lcd->lockPositionOnSecondLine(currentLetterIndex);

    joystickLeftRightMove move = joystick->movedLeftRight();

    if (move == Left) {
        --currentLetterIndex;
        if (currentLetterIndex < nicknameStartPos)
            currentLetterIndex = nicknameEndPos;
    }
    else if (move == Right) {
        ++currentLetterIndex;
        if (currentLetterIndex > nicknameEndPos)
            currentLetterIndex = nicknameStartPos;
    }

    if (joystick->pressedButton()) {
        lcd->unlockPositionOnSecondLine(currentLetterIndex);

        if (currentLetterIndex == nicknameEndPos) {
            for (byte i = 0; i < nicknameLen; ++i) 
                playerNickname[i] = nicknameLine[nicknameStartPos + i];
            return menuActionIndex;
        }

        state = changeLetter;
    }

    return registerActionIndex;
}

ActionIndex Register::runChangeLetter() {
    joystickUpDownMove move = joystick->movedUpDown();

    if (move == Up) 
        nicknameLine[currentLetterIndex] = getNextLetter(nicknameLine[currentLetterIndex]);
    else if (move == Down) 
        nicknameLine[currentLetterIndex] = getPrevLetter(nicknameLine[currentLetterIndex]);

    if (joystick->pressedButton()) {
        state = selectLetterIndex;
        lcd->lockPositionOnSecondLine(currentLetterIndex);
    }

    return registerActionIndex;
}

char Register::getNextLetter(char ch) {
    if (ch == ' ')
        return 'a';
    if (ch == 'z')
        return ' ';
    return ch + 1;
}

char Register::getPrevLetter(char ch) {
    if (ch == 'a')
        return ' ';
    if (ch == ' ')
        return 'z';
    return ch - 1;
}
