#ifndef BUZZER_H
#define BUZZER_H

#include "../../include/utils.h"
#include "../game/theme_song.h"
	
class Buzzer  {
	static const byte buzzerPin = 3;

    unsigned long lastPause = 0;
    byte currentNote = 0;

public:
    Buzzer() {};
    void playThemeSong();
};

#endif