#include "buzzer.h" 

/*

    We cannot affort the luxury of saving the songs in memory
    Thus, one option is to hardcode them

    A python script was used to generate the code
*/

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
    if (soundTypeIndex[(byte)soundState] == 0)
        playNote(391, 47, 0);
    else if (soundTypeIndex[(byte)soundState] == 1)
        playNote(415, 47, 117);
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
    if (soundTypeIndex[(byte)soundState] == 0)
        playNote(660, 100, 600);
    else if (soundTypeIndex[(byte)soundState] == 1)
        playNote(660, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 2)
        playNote(660, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 3)
        playNote(510, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 4)
        playNote(660, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 5)
        playNote(770, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 6)
        playNote(380, 100, 550);
    else if (soundTypeIndex[(byte)soundState] == 7)
        playNote(510, 100, 575);
    else if (soundTypeIndex[(byte)soundState] == 8)
        playNote(380, 100, 450);
    else if (soundTypeIndex[(byte)soundState] == 9)
        playNote(320, 100, 400);
    else if (soundTypeIndex[(byte)soundState] == 10)
        playNote(440, 100, 500);
    else if (soundTypeIndex[(byte)soundState] == 11)
        playNote(480, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 12)
        playNote(450, 100, 330);
    else if (soundTypeIndex[(byte)soundState] == 13)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 14)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 15)
        playNote(660, 80, 200);
    else if (soundTypeIndex[(byte)soundState] == 16)
        playNote(760, 50, 200);
    else if (soundTypeIndex[(byte)soundState] == 17)
        playNote(860, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 18)
        playNote(700, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 19)
        playNote(760, 50, 150);
    else if (soundTypeIndex[(byte)soundState] == 20)
        playNote(660, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 21)
        playNote(520, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 22)
        playNote(580, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 23)
        playNote(480, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 24)
        playNote(510, 100, 500);
    else if (soundTypeIndex[(byte)soundState] == 25)
        playNote(380, 100, 450);
    else if (soundTypeIndex[(byte)soundState] == 26)
        playNote(320, 100, 400);
    else if (soundTypeIndex[(byte)soundState] == 27)
        playNote(440, 100, 500);
    else if (soundTypeIndex[(byte)soundState] == 28)
        playNote(480, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 29)
        playNote(450, 100, 330);
    else if (soundTypeIndex[(byte)soundState] == 30)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 31)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 32)
        playNote(660, 80, 200);
    else if (soundTypeIndex[(byte)soundState] == 33)
        playNote(760, 50, 200);
    else if (soundTypeIndex[(byte)soundState] == 34)
        playNote(860, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 35)
        playNote(700, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 36)
        playNote(760, 50, 150);
    else if (soundTypeIndex[(byte)soundState] == 37)
        playNote(660, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 38)
        playNote(520, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 39)
        playNote(580, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 40)
        playNote(480, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 41)
        playNote(500, 100, 500);
    else if (soundTypeIndex[(byte)soundState] == 42)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 43)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 44)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 45)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 46)
        playNote(650, 150, 300);
    else if (soundTypeIndex[(byte)soundState] == 47)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 48)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 49)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 50)
        playNote(430, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 51)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 52)
        playNote(570, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 53)
        playNote(500, 100, 220);
    else if (soundTypeIndex[(byte)soundState] == 54)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 55)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 56)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 57)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 58)
        playNote(650, 200, 300);
    else if (soundTypeIndex[(byte)soundState] == 59)
        playNote(1020, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 60)
        playNote(1020, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 61)
        playNote(1020, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 62)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 63)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 64)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 65)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 66)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 67)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 68)
        playNote(650, 150, 300);
    else if (soundTypeIndex[(byte)soundState] == 69)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 70)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 71)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 72)
        playNote(430, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 73)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 74)
        playNote(570, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 75)
        playNote(585, 100, 420);
    else if (soundTypeIndex[(byte)soundState] == 76)
        playNote(550, 100, 450);
    else if (soundTypeIndex[(byte)soundState] == 77)
        playNote(500, 100, 420);
    else if (soundTypeIndex[(byte)soundState] == 78)
        playNote(380, 100, 360);
    else if (soundTypeIndex[(byte)soundState] == 79)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 80)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 81)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 82)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 83)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 84)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 85)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 86)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 87)
        playNote(650, 150, 300);
    else if (soundTypeIndex[(byte)soundState] == 88)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 89)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 90)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 91)
        playNote(430, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 92)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 93)
        playNote(570, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 94)
        playNote(500, 100, 220);
    else if (soundTypeIndex[(byte)soundState] == 95)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 96)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 97)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 98)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 99)
        playNote(650, 200, 300);
    else if (soundTypeIndex[(byte)soundState] == 100)
        playNote(1020, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 101)
        playNote(1020, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 102)
        playNote(1020, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 103)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 104)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 105)
        playNote(760, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 106)
        playNote(720, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 107)
        playNote(680, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 108)
        playNote(620, 150, 150);
    else if (soundTypeIndex[(byte)soundState] == 109)
        playNote(650, 150, 300);
    else if (soundTypeIndex[(byte)soundState] == 110)
        playNote(380, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 111)
        playNote(430, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 112)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 113)
        playNote(430, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 114)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 115)
        playNote(570, 100, 100);
    else if (soundTypeIndex[(byte)soundState] == 116)
        playNote(585, 100, 420);
    else if (soundTypeIndex[(byte)soundState] == 117)
        playNote(550, 100, 450);
    else if (soundTypeIndex[(byte)soundState] == 118)
        playNote(500, 100, 420);
    else if (soundTypeIndex[(byte)soundState] == 119)
        playNote(380, 100, 360);
    else if (soundTypeIndex[(byte)soundState] == 120)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 121)
        playNote(500, 100, 300);
    else if (soundTypeIndex[(byte)soundState] == 122)
        playNote(500, 100, 150);
    else if (soundTypeIndex[(byte)soundState] == 123)
        playNote(500, 60, 300);
    else if (soundTypeIndex[(byte)soundState] == 124)
        playNote(500, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 125)
        playNote(500, 60, 300);
    else if (soundTypeIndex[(byte)soundState] == 126)
        playNote(500, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 127)
        playNote(580, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 128)
        playNote(660, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 129)
        playNote(500, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 130)
        playNote(430, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 131)
        playNote(380, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 132)
        playNote(500, 60, 600);
    else if (soundTypeIndex[(byte)soundState] == 133)
        playNote(500, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 134)
        playNote(500, 60, 300);
    else if (soundTypeIndex[(byte)soundState] == 135)
        playNote(500, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 136)
        playNote(580, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 137)
        playNote(660, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 138)
        playNote(870, 80, 550);
    else if (soundTypeIndex[(byte)soundState] == 139)
        playNote(760, 80, 325);
    else if (soundTypeIndex[(byte)soundState] == 140)
        playNote(500, 60, 600);
    else if (soundTypeIndex[(byte)soundState] == 141)
        playNote(500, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 142)
        playNote(500, 60, 300);
    else if (soundTypeIndex[(byte)soundState] == 143)
        playNote(500, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 144)
        playNote(580, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 145)
        playNote(660, 80, 350);
    else if (soundTypeIndex[(byte)soundState] == 146)
        playNote(500, 80, 150);
    else if (soundTypeIndex[(byte)soundState] == 147)
        playNote(430, 80, 300);
    else if (soundTypeIndex[(byte)soundState] == 148)
        playNote(380, 80, 150);
}