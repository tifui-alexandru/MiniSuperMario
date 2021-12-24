#ifndef EEPROM_H
#define EEPROM_H

/*
    Manipulates EEPROM I/O operations.
*/

#include <Arduino.h>
#include <EEPROM.h>
	
// nickname: 6 bytes
// highscore: 3 bytes 
// total chunk: 9 bytes

// keep eeprom values sorted by highscore
class EepromClass {
    static const byte chunkSize = 9;
    static const byte noOfPlayers = 3;

    static const byte highscoreSize = 6; // number of digits in base 10
    char currentStringHighscore[highscoreSize];

    static const byte nicknameSize = 6;
    char currentNickname[nicknameSize];
    char nextNickname[nicknameSize];

    static const byte outputStringSize = 16;
    char outputString[outputStringSize];

    static const byte matrixIntensityOffset = noOfPlayers * chunkSize;
    static const byte lcdIntensityOffset = noOfPlayers * chunkSize + 1;
    static const byte lcdContrastOffset = noOfPlayers * chunkSize + 2;

    static const byte noOfActivePlayersOffset = lcdContrastOffset + 1;

    const byte byteMask = 0xFF;
    const byte byteSize = 8;

    byte noOfActivePlayers = 0;

    void readNickname(byte, char*);
    int readHighscore(byte);
    void writeNickname(byte, char*);
    void writeHighscore(byte, int);

    bool checkScorePresence(char*, int);

    bool stringEq(char*, char*);

public:
    void initSetup();
    bool write(char*, int);
    char* read(byte);
    byte getNoOfScores() { return noOfActivePlayers; }

    void resetScoreboard();

    void writeMatrixIntensity(byte value) { EEPROM.update(matrixIntensityOffset, value); }
    void writeLcdIntensity(byte value) { EEPROM.update(lcdIntensityOffset, value); }
    void writeLcdContrast(byte value) { EEPROM.update(lcdContrastOffset, value); }

    byte readMatrixIntensity() { return EEPROM.read(matrixIntensityOffset); }
    byte readLcdIntensity() { return EEPROM.read(lcdIntensityOffset); }
    byte readLcdContrast() { return EEPROM.read(lcdContrastOffset); }
};

#endif