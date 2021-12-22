#include "buzzer.h" 

// call tone(buzzerPin, frequency, duration) after a delay of 'pause' milliseconds
void Buzzer::playNote(unsigned int frequency, unsigned long duration, unsigned long pause) {
    unsigned long now = millis();
    if (now - lastPause > pause) {
        lastPause = now;
        tone(buzzerPin, frequency, duration);

        if (++soundTypeIndex[(byte)soundState] == soundTypeLength[(byte)soundState]) {
            soundTypeIndex[(byte)soundState] = 0;
            soundState = themeSong;
        }
    }
}

void Buzzer::playSound() {
    if (soundState == themeSong)
        buzzThemeSong();
    else if (soundState == jumpSound)
        buzzJumpSound();
    else if (soundState == coinSound)
        buzzCoinSound();
    else if (soundState == deathTune)
        buzzDeathTune();
    else if (soundState == nextLevelTune)
        buzzNextLevelTune();
}

void Buzzer::buzzJumpSound() {
    soundState = themeSong;
}

void Buzzer::buzzDeathTune() {
    soundState = themeSong;
}

void Buzzer::buzzNextLevelTune() {
    soundState = themeSong;
}

void Buzzer::buzzCoinSound() {
    if (soundTypeIndex[(byte)soundState] == 0)
        playNote(NOTE_B5, 100, 0);
    else if (soundTypeIndex[(byte)soundState] == 1)
        playNote(NOTE_E6, 300, 100);
}

void Buzzer::buzzThemeSong() {
    // tone(buzzerPin, 660, 100);
    // delay(150);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 510, 100);
    // delay(100);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 770, 100);
    // delay(550);
    // tone(buzzerPin, 380, 100);
    // delay(575);

    // tone(buzzerPin, 510, 100);
    // delay(450);
    // tone(buzzerPin, 380, 100);
    // delay(400);
    // tone(buzzerPin, 320, 100);
    // delay(500);
    // tone(buzzerPin, 440, 100);
    // delay(300);
    // tone(buzzerPin, 480, 80);
    // delay(330);
    // tone(buzzerPin, 450, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(200);
    // tone(buzzerPin, 660, 80);
    // delay(200);
    // tone(buzzerPin, 760, 50);
    // delay(150);
    // tone(buzzerPin, 860, 100);
    // delay(300);
    // tone(buzzerPin, 700, 80);
    // delay(150);
    // tone(buzzerPin, 760, 50);
    // delay(350);
    // tone(buzzerPin, 660, 80);
    // delay(300);
    // tone(buzzerPin, 520, 80);
    // delay(150);
    // tone(buzzerPin, 580, 80);
    // delay(150);
    // tone(buzzerPin, 480, 80);
    // delay(500);

    // tone(buzzerPin, 510, 100);
    // delay(450);
    // tone(buzzerPin, 380, 100);
    // delay(400);
    // tone(buzzerPin, 320, 100);
    // delay(500);
    // tone(buzzerPin, 440, 100);
    // delay(300);
    // tone(buzzerPin, 480, 80);
    // delay(330);
    // tone(buzzerPin, 450, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(200);
    // tone(buzzerPin, 660, 80);
    // delay(200);
    // tone(buzzerPin, 760, 50);
    // delay(150);
    // tone(buzzerPin, 860, 100);
    // delay(300);
    // tone(buzzerPin, 700, 80);
    // delay(150);
    // tone(buzzerPin, 760, 50);
    // delay(350);
    // tone(buzzerPin, 660, 80);
    // delay(300);
    // tone(buzzerPin, 520, 80);
    // delay(150);
    // tone(buzzerPin, 580, 80);
    // delay(150);
    // tone(buzzerPin, 480, 80);
    // delay(500);

    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 150);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(150);

    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 430, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(100);
    // tone(buzzerPin, 570, 100);
    // delay(220);

    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 200);
    // delay(300);

    // tone(buzzerPin, 1020, 80);
    // delay(300);
    // tone(buzzerPin, 1020, 80);
    // delay(150);
    // tone(buzzerPin, 1020, 80);
    // delay(300);

    // tone(buzzerPin, 380, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 150);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(150);

    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 430, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(100);
    // tone(buzzerPin, 570, 100);
    // delay(420);

    // tone(buzzerPin, 585, 100);
    // delay(450);

    // tone(buzzerPin, 550, 100);
    // delay(420);

    // tone(buzzerPin, 500, 100);
    // delay(360);

    // tone(buzzerPin, 380, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 150);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(150);

    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 430, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(100);
    // tone(buzzerPin, 570, 100);
    // delay(220);

    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 200);
    // delay(300);

    // tone(buzzerPin, 1020, 80);
    // delay(300);
    // tone(buzzerPin, 1020, 80);
    // delay(150);
    // tone(buzzerPin, 1020, 80);
    // delay(300);

    // tone(buzzerPin, 380, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 760, 100);
    // delay(100);
    // tone(buzzerPin, 720, 100);
    // delay(150);
    // tone(buzzerPin, 680, 100);
    // delay(150);
    // tone(buzzerPin, 620, 150);
    // delay(300);

    // tone(buzzerPin, 650, 150);
    // delay(300);
    // tone(buzzerPin, 380, 100);
    // delay(150);
    // tone(buzzerPin, 430, 100);
    // delay(150);

    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 430, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(100);
    // tone(buzzerPin, 570, 100);
    // delay(420);

    // tone(buzzerPin, 585, 100);
    // delay(450);

    // tone(buzzerPin, 550, 100);
    // delay(420);

    // tone(buzzerPin, 500, 100);
    // delay(360);

    // tone(buzzerPin, 380, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(300);
    // tone(buzzerPin, 500, 100);
    // delay(150);
    // tone(buzzerPin, 500, 100);
    // delay(300);

    // tone(buzzerPin, 500, 60);
    // delay(150);
    // tone(buzzerPin, 500, 80);
    // delay(300);
    // tone(buzzerPin, 500, 60);
    // delay(350);
    // tone(buzzerPin, 500, 80);
    // delay(150);
    // tone(buzzerPin, 580, 80);
    // delay(350);
    // tone(buzzerPin, 660, 80);
    // delay(150);
    // tone(buzzerPin, 500, 80);
    // delay(300);
    // tone(buzzerPin, 430, 80);
    // delay(150);
    // tone(buzzerPin, 380, 80);
    // delay(600);

    // tone(buzzerPin, 500, 60);
    // delay(150);
    // tone(buzzerPin, 500, 80);
    // delay(300);
    // tone(buzzerPin, 500, 60);
    // delay(350);
    // tone(buzzerPin, 500, 80);
    // delay(150);
    // tone(buzzerPin, 580, 80);
    // delay(150);
    // tone(buzzerPin, 660, 80);
    // delay(550);

    // tone(buzzerPin, 870, 80);
    // delay(325);
    // tone(buzzerPin, 760, 80);
    // delay(600);

    // tone(buzzerPin, 500, 60);
    // delay(150);
    // tone(buzzerPin, 500, 80);
    // delay(300);
    // tone(buzzerPin, 500, 60);
    // delay(350);
    // tone(buzzerPin, 500, 80);
    // delay(150);
    // tone(buzzerPin, 580, 80);
    // delay(350);
    // tone(buzzerPin, 660, 80);
    // delay(150);
    // tone(buzzerPin, 500, 80);
    // delay(300);
    // tone(buzzerPin, 430, 80);
    // delay(150);
    // tone(buzzerPin, 380, 80);
    // delay(600);

    // tone(buzzerPin, 660, 100);
    // delay(150);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 510, 100);
    // delay(100);
    // tone(buzzerPin, 660, 100);
    // delay(300);
    // tone(buzzerPin, 770, 100);
    // delay(550);
    // tone(buzzerPin, 380, 100);
    // delay(575);
}