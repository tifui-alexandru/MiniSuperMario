#ifndef BUZZER_H
#define BUZZER_H

#include "utils.h"
#include "../game/pitches.h"
	
class Buzzer  {
	static const byte buzzerPin = A4; // if it works, don't touch it

    unsigned long lastPause = 0;
    byte currentNote = 0;
    
    static const byte noOfSoundTypes = 5;

    enum SoundType {
        themeSong,
        jumpSound,
        coinSound,
        deathTune,
        nextLevelTune
    };

    SoundType soundState = themeSong;

    const byte soundTypeLength[noOfSoundTypes] = {149, 2, 2, 2, 2};
    byte soundTypeIndex[noOfSoundTypes] = {0, 0, 0, 0, 0};

    void playNote(unsigned int, unsigned long, unsigned long);

    void buzzThemeSong();
    void buzzJumpSound();
    void buzzCoinSound();
    void buzzDeathTune();
    void buzzNextLevelTune();

public:
    Buzzer() {};

    void playSound();

    void playThemeSong() { soundState = themeSong; }
    void playJumpSound() { soundState = jumpSound; }
    void playCoinSound() { soundState = coinSound; }
    void playDeathTune() { soundState = deathTune; }
    void playNextLevelTune() { soundState = nextLevelTune; }
};

#endif