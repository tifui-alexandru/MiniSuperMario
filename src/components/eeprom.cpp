#include "eeprom.h"

void EepromClass::initSetup() {
    // EEPROM.update(noOfActivePlayersOffset, 0);
    noOfActivePlayers = EEPROM.read(noOfActivePlayersOffset);
}

char* EepromClass::readNickname(uint8_t playerIndex) {
    if (playerIndex < noOfActivePlayers)
        return nullptr;

    for (uint8_t i = 0; i < nicknameSize; ++i)
        currentNickname[i] = EEPROM.read(playerIndex * chunkSize + i);

    return currentNickname;
}

int EepromClass::readHighscore(uint8_t playerIndex) {
    if (playerIndex < noOfActivePlayers)
        return -1;

    uint8_t highscoreByte1 = EEPROM.read(playerIndex * chunkSize + nicknameSize);
    uint8_t highscoreByte2 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 1);
    uint8_t highscoreByte3 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 2);

    return (highscoreByte3 << (2 * byteSize)) | (highscoreByte2 << byteSize) | highscoreByte1;
}

void EepromClass::writeNickname(uint8_t playerIndex, char* newNickname) {
    for (uint8_t i = 0; i < nicknameSize; ++i)
        EEPROM.update(playerIndex * chunkSize + i, newNickname[i]);
}

void EepromClass::writeHighscore(uint8_t playerIndex, int newHighscore) {
    uint8_t highscoreByte1 = newHighscore & byteMask;
    uint8_t highscoreByte2 = (newHighscore >> byteSize) & byteMask;
    uint8_t highscoreByte3 = (newHighscore >> (2 * byteSize)) & byteMask;

    EEPROM.update(playerIndex * chunkSize + nicknameSize, highscoreByte1);
    EEPROM.update(playerIndex * chunkSize + nicknameSize + 1, highscoreByte2);
    EEPROM.update(playerIndex * chunkSize + nicknameSize + 2, highscoreByte3);
}

// checks if a score is already registered in top 3
bool EepromClass::checkScorePresence(char* nickname, int highscore) {
    for (uint8_t idx = 0; idx < noOfActivePlayers; ++idx) {
        if (highscore == readHighscore(idx) and stringEq(nickname, readNickname(0))) 
            return true;
    }
    return false;
}

// returns true if player entered the podium
bool EepromClass::write(char* nickname, int highscore) {
    if (checkScorePresence(nickname, highscore)) 
        return false;

    if (noOfActivePlayers < noOfPlayers) {
        writeNickname(noOfActivePlayers, nickname);
        writeHighscore(noOfActivePlayers, highscore);

        // count the new player
        ++noOfActivePlayers;
        EEPROM.update(noOfActivePlayersOffset, noOfActivePlayers);
    }
    else {
        int lowestHighscore = readHighscore(noOfPlayers);
        if (lowestHighscore >= highscore) 
            return false; // the new highscore is not in top 3
        
        // else replace the lowest highscore
        writeNickname(noOfPlayers, nickname);
        writeHighscore(noOfPlayers, highscore);
    }

    // keep the EEPROM sorted by pushing the new inserted value to its place

    uint8_t currentIndex = noOfActivePlayers - 1;
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

        delete[] nextNickname;
    } 

    return true;
}

// return the string in the format it will be displayed
char* EepromClass::read(uint8_t playerIndex) {
    if (playerIndex >= noOfActivePlayers)
        return nullptr;

    char* nickname = new char[nicknameSize];
    nickname = readNickname(playerIndex);

    int highscore = readHighscore(highscore);
    char* stringHighscore = new char[highscoreSize];

    for (uint8_t i = 0; i < highscoreSize; ++i)
        stringHighscore[i] = ' ';
    if (highscore == 0)
        stringHighscore[0] = '0';
    else {
        uint8_t currPos = 0;
        while (highscore > 0) {
            uint8_t lastDigit = highscore % 10;
            highscore /= 10;
            stringHighscore[currPos++] = char(lastDigit + '0');
        }

        // reverse
        for (uint8_t i = 0, j = highscoreSize; i < j; ++i, --j) {
            char aux = stringHighscore[i];
            stringHighscore[i] = stringHighscore[j];
            stringHighscore[j] = aux;
        }
    }

    // construct the final string
    outputString[0] = char(playerIndex + 1 + '0');
    outputString[1] = '.';
    outputString[2] = ' ';

    for (uint8_t i = 0; i < nicknameSize; ++i)
        outputString[3 + i] = nickname[i];

    outputString[3 + nicknameSize] = ' ';

    for (uint8_t i = 0; i < highscoreSize; ++i)
        outputString[3 + nicknameSize + 1 + i] = stringHighscore[i];

    delete[] nickname;
    delete[] stringHighscore;

    return outputString; 
}

bool EepromClass::stringEq(char* str1, char* str2) {
    for (uint8_t i = 0; i < nicknameSize; ++i)
        if (str1[i] != str2[i])
            return false;
    return true;
}