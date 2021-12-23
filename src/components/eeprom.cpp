#include "eeprom.h"

void EepromClass::initSetup() {
    noOfActivePlayers = EEPROM.read(noOfActivePlayersOffset);
}

void EepromClass::resetScoreboard() {
    noOfActivePlayers = 0;
    EEPROM.update(noOfActivePlayersOffset, 0);
}

// read nickname and place it in storingString variable
void EepromClass::readNickname(byte playerIndex, char* storingString) {
    if (playerIndex >= noOfActivePlayers)
        return;

    for (byte i = 0; i < nicknameSize; ++i)
        storingString[i] = EEPROM.read(playerIndex * chunkSize + i);
}

int EepromClass::readHighscore(byte playerIndex) {
    if (playerIndex >= noOfActivePlayers)
        return -1;

    byte highscoreByte1 = EEPROM.read(playerIndex * chunkSize + nicknameSize);
    byte highscoreByte2 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 1);
    byte highscoreByte3 = EEPROM.read(playerIndex * chunkSize + nicknameSize + 2);

    return (highscoreByte3 << (2 * byteSize)) | (highscoreByte2 << byteSize) | highscoreByte1;
}

void EepromClass::writeNickname(byte playerIndex, char* newNickname) {
    for (byte i = 0; i < nicknameSize; ++i)
        EEPROM.update(playerIndex * chunkSize + i, newNickname[i]);
}

void EepromClass::writeHighscore(byte playerIndex, int newHighscore) {
    byte highscoreByte1 = newHighscore & byteMask;
    byte highscoreByte2 = (newHighscore >> byteSize) & byteMask;
    byte highscoreByte3 = (newHighscore >> (2 * byteSize)) & byteMask;

    EEPROM.update(playerIndex * chunkSize + nicknameSize, highscoreByte1);
    EEPROM.update(playerIndex * chunkSize + nicknameSize + 1, highscoreByte2);
    EEPROM.update(playerIndex * chunkSize + nicknameSize + 2, highscoreByte3);
}

// checks if a score is already registered in top 3
bool EepromClass::checkScorePresence(char* nickname, int highscore) {
    for (byte idx = 0; idx < noOfActivePlayers; ++idx) {
        readNickname(idx, currentNickname);
        if (highscore == readHighscore(idx) and stringEq(nickname, currentNickname)) 
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
        int lowestHighscore = readHighscore(noOfPlayers - 1);
        if (lowestHighscore >= highscore) 
            return false; // the new highscore is not in top 3
        
        // else replace the lowest highscore
        writeNickname(noOfPlayers, nickname);
        writeHighscore(noOfPlayers, highscore);
    }

    // keep the EEPROM sorted by pushing the new inserted value to its place

    byte currentIndex = noOfActivePlayers - 1;
    while (currentIndex > 0) {
        int nextHighscore = readHighscore(currentIndex - 1);
        if (nextHighscore >= highscore)
            break; // we found the last lastPosition
        
        readNickname(currentIndex - 1, nextNickname);

        writeNickname(currentIndex, nextNickname);
        writeHighscore(currentIndex, nextHighscore);

        writeNickname(currentIndex - 1, nickname);
        writeHighscore(currentIndex - 1, highscore);

        currentIndex -= 1;
    } 

    return true;
}

// return the string in the format it will be displayed
char* EepromClass::read(byte playerIndex) {
    if (playerIndex >= noOfActivePlayers)
        return nullptr;

    readNickname(playerIndex, currentNickname);
    int highscore = readHighscore(playerIndex);

    for (byte i = 0; i < highscoreSize; ++i)
        currentStringHighscore[i] = ' ';

    // convert highscore to string 
    if (highscore == 0)
        currentStringHighscore[0] = '0';
    else {
        byte currPos = 0;
        while (highscore > 0) {
            byte lastDigit = highscore % 10;
            highscore /= 10;
            currentStringHighscore[currPos++] = char(lastDigit + '0');
        }

        // reverse
        for (byte i = 0, j = currPos - 1; i < j; ++i, --j) {
            char aux = currentStringHighscore[i];
            currentStringHighscore[i] = currentStringHighscore[j];
            currentStringHighscore[j] = aux;
        }
    }

    // construct the final string
    outputString[0] = char(playerIndex + 1 + '0');
    outputString[1] = '.';
    outputString[2] = ' ';

    for (byte i = 0; i < nicknameSize; ++i)
        outputString[3 + i] = currentNickname[i];

    outputString[3 + nicknameSize] = ' ';

    for (byte i = 0; i < highscoreSize; ++i)
        outputString[3 + nicknameSize + 1 + i] = currentStringHighscore[i];

    return outputString; 
}

bool EepromClass::stringEq(char* str1, char* str2) {
    for (byte i = 0; i < nicknameSize; ++i)
        if (str1[i] != str2[i])
            return false;
    return true;
}