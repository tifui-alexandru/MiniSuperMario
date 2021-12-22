#ifndef BUZZER_H
#define BUZZER_H

#include "utils.h"
#include "../game/pitches.h"
	
class Buzzer  {
	static const byte buzzerPin = A4; // if it works, don't touch it

    unsigned long lastPause = 0;
    byte currentNote = 0;

    enum SoundType {
        themeSong,
        jumpSound,
        coinSound,
        deathTune,
        nextLevelTune
    };

    SoundType currentSound = themeSong;

    static const byte themeSongLenght = 2;
    static const byte jumpSoundLenght = 2;
    static const byte coinSoundLenght = 2;
    static const byte deathTuneLenght = 2;
    static const byte nextLevelTuneLenght = 2;

    void playNote(unsigned int, unsigned long, unsigned long);

    void playThemeSong();
    void playJumpSound();
    void playCoinSound();
    void playDeathTune();
    void playNextLevelTune();

public:
    Buzzer() {};

    void playSound();
};

#endif