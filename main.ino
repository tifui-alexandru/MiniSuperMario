#include "include/menu.h"
#include "include/wellcome.h"
#include "include/play.h"
#include "include/how_to_play.h"
#include "include/hall_of_fame.h"
#include "include/settings.h"
#include "include/about.h"

#include "include/lcd.h"
#include "include/joystick.h"
#include "include/matrix.h"

#include "include/utils.h"

Lcd* lcd = new Lcd();
Joystick* joystick = new Joystick();
Matrix* gameMap = new Matrix();

byte currentActionIndex;
const byte noOfactions = 7;
Action* actions[noOfactions];

void initializeActions() {
    actions[0] = new Wellcome(lcd, joystick, gameMap);
    actions[1] = new Menu(lcd, joystick, gameMap);
    actions[2] = new Play(lcd, joystick, gameMap);
    actions[3] = new HowToPlay(lcd, joystick, gameMap);
    actions[4] = new HallOfFame(lcd, joystick, gameMap);
    actions[5] = new Settings(lcd, joystick, gameMap);
    actions[6] = new About(lcd, joystick, gameMap);
}

void setup() {
    lcd->initSetup();
    gameMap->initSetup();

    initializeActions();

    for (byte i = 0; i < noOfactions; ++i) 
        actions[i]->initSetup();
        
    currentActionIndex = 0; // Wellcome
    Serial.begin(9600);
}

void loop() {
    ActionIndex nextActionIndex = actions[currentActionIndex]->run();
    currentActionIndex = int(nextActionIndex);
}