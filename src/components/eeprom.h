#ifndef EEPROM_H
#define EEPROM_H

#include <EEPROM.h>
	
// nickname: 6 bytes
// highscore: 3 bytes 
// total chunk: 9 bytes

// keep eeprom values sorted by highscore
class EepromClass {
    static const uint8_t chunkSize = 9;
    static const uint8_t nicknameSize = 6;
    static const uint8_t highscoreSize = 6; // number of digits in base 10
    static const uint8_t outputStringSize = 16;
    static const uint8_t noOfPlayers = 3;

    static const uint8_t matrixIntensityOffset = noOfPlayers * chunkSize;
    static const uint8_t lcdIntensityOffset = noOfPlayers * chunkSize + 1;
    static const uint8_t lcdContrastOffset = noOfPlayers * chunkSize + 2;

    const uint8_t byteMask = 0xFF;
    const uint8_t byteSize = 8;

    uint8_t noOfActivePlayers = 0;

    char *readNickname(uint8_t);
    int readHighscore(uint8_t);
    void writeNickname(uint8_t, char*);
    void writeHighscore(uint8_t, int);

public:
    void write(char*, int);
    char* read(uint8_t);
    uint8_t getNoOfScores() { return noOfActivePlayers; }

    void writeMatrixIntensity(uint8_t value) { EEPROM.update(matrixIntensityOffset, value); }
    void writeLcdIntensity(uint8_t value) { EEPROM.update(lcdIntensityOffset, value); }
    void writeLcdContrast(uint8_t value) { EEPROM.update(lcdContrastOffset, value); }

    uint8_t readMatrixIntensity() { return EEPROM.read(matrixIntensityOffset); }
    uint8_t readLcdIntensity() { return EEPROM.read(lcdIntensityOffset); }
    uint8_t readLcdContrast() { return EEPROM.read(lcdContrastOffset); }
};

#endif