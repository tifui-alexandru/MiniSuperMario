#include "../include/eeprom.h"

char* EepromClass::readNickname(int playerIndex) {
    if (playerIndex < noOfActivePlayers)
        return nullptr;

    char answer[nicknameSize];
    for (int i = 0; i < nicknameSize; ++i)
        answer[i] = EEPROM.read(playerIndex * chunkSize + i);

    return answer;
}

int EepromClass::readHighscore(int playerIndex) {
    if (playerIndex < noOfActivePlayers)
        return -1;

    byte highscoreByte1 = EEPROM.read(playerIndex * chunkSize + nicknameSize);
    byte highscoreByte2 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 1);
    byte highscoreByte3 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 2);

    return (highscoreByte3 << (2 * byteSize)) | (highscoreByte2 << byteSize) | highscoreByte1;
}

void EepromClass::writeNickname(int playerIndex, char* newNickname) {
    for (int i = 0; i < nicknameSize; ++i)
        EEPROM.update(playerIndex * chunkSize + i, newNickname[i]);
}

void EepromClass::writeHighscore(int playerIndex, int newHighscore) {
    byte highscoreByte1 = newHighscore & byteMask;
    byte highscoreByte2 = (newHighscore >> byteSize) & byteMask;
    byte highscoreByte3 = (newHighscore >> (2 * byteSize)) & byteMask;

    EEPROM.update(highscoreByte1, playerIndex * chunkSize + nicknameSize);
    EEPROM.update(highscoreByte2, playerIndex * chunkSize + nicknameSize + 1);
    EEPROM.update(highscoreByte3, playerIndex * chunkSize + nicknameSize + 2);
}

void EepromClass::write(char* nickname, int highscore) {
    if (noOfActivePlayers < noOfPlayers) {
        writeNickname(noOfActivePlayers, nickname);
        writeHighscore(noOfActivePlayers, highscore);
        ++noOfActivePlayers;
    }
    else {
        int lowestHighscore = readHighscore(noOfPlayers);
        if (lowestHighscore >= highscore) 
            return; // the new highscore is not in top 3
        
        // else replace the lowest highscore
        writeNickname(noOfPlayers, nickname);
        writeHighscore(noOfPlayers, highscore);
    }

    // keep the EEPROM sorted by pushing the new inserted value to its place

    int currentIndex = noOfActivePlayers - 1;
    while (currentIndex > 0) {
        int nextHighscore = readHighscore(currentIndex - 1);
        if (nextHighscore >= highscore)
            break; // we found the last lastPosition
        
        char* nextNickname = new char[nicknameSize];
        nextNickname = readNickname(currentIndex - 1);

        writeNickname(currentIndex, nextNickname);
        writeHighscore(currentIndex, nextHighscore);

        writeNickname(currentIndex - 1, nickname);
        writeHighscore(currentIndex - 1, highscore);

        currentIndex -= 1;
    } 
}

// return the string in the format it will be displayed
char* EepromClass::read(int playerIndex) {
    if (playerIndex < noOfActivePlayers)
        return nullptr;

    char* answer = new char[EepromClass::outputStringSize];

    char* nickname = new char[nicknameSize];
    nickname = readNickname(playerIndex);

    int highscore = readHighscore(highscore);
    char* stringHighscore = new char[highscoreSize];

    for (int i = 0; i < highscoreSize; ++i)
        stringHighscore[i] = ' ';
    if (highscore == 0)
        stringHighscore[0] = '0';
    else {
        int currPos = 0;
        while (highscore > 0) {
            int lastDigit = highscore % 10;
            highscore /= 10;
            stringHighscore[currPos++] = char(lastDigit + '0');
        }

        // reverse
        for (int i = 0, j = highscoreSize; i < j; ++i, --j) {
            char aux = stringHighscore[i];
            stringHighscore[i] = stringHighscore[j];
            stringHighscore[j] = aux;
        }
    }

    // construct the final string
    answer[0] = char(playerIndex + 1 + '0');
    answer[1] = '.';
    answer[2] = ' ';

    for (int i = 0; i < nicknameSize; ++i)
        answer[3 + i] = nickname[i];

    answer[3 + nicknameSize] = ' ';
    
    for (int i = 0; i < highscoreSize; ++i)
        answer[3 + nicknameSize + 1 + i] = stringHighscore[i];

    return answer; 
}