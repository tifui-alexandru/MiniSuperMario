#ifndef EEPROM_H
#define EEPROM_H

#include <EEPROM.h>
	
// nickname: 6 bytes
// highscore: 3 bytes 
// total chunk: 9 bytes

// keep eeprom values sorted by highscore
class EepromClass {
    void sort();

    static const byte chunkSize = 9;
    static const byte nicknameSize = 6;
    static const byte highscoreSize = 6; // number of digits in base 10
    static const byte outputStringSize = 16;
    static const byte noOfPlayers = 3;

    const int byteMask = 0xFF;
    const int byteSize = 8;

    int noOfActivePlayers = 0;

    char* readNickname(int);
    int readHighscore(int);
    void writeNickname(int, char*);
    void writeHighscore(int, int);

public:
    void write(char*, int);
    char* read(int);
    int getNoOfScores() { return noOfActivePlayers; }
};

#endif