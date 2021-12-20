#ifndef BUZZER_H
#define BUZZER_H

#include "../../include/utils.h"
#include "../game/theme_song.h"
	
class Buzzer  {
	static const int buzzerPin = 3;

    unsigned long lastPause = 0;
    byte currentNote = 0;

public:
    Buzzer() {};
    void initSetup();
    void playThemeSong();
};

#endif