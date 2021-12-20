#include "src/actions/menu.h"
#include "src/actions/wellcome.h"
#include "src/actions/play.h"
#include "src/actions/how_to_play.h"
#include "src/actions/hall_of_fame.h"
#include "src/actions/settings.h"
#include "src/actions/about.h"
#include "src/actions/register.h"

#include "src/components/lcd.h"
#include "src/components/joystick.h"
#include "src/components/matrix.h"
#include "src/components/buzzer.h"
#include "src/components/eeprom.h"

#include "include/utils.h"

Lcd* lcd = new Lcd();
Joystick* joystick = new Joystick();
Matrix* gameMap = new Matrix();
Buzzer* buzzer = new Buzzer();
EepromClass* eepromObj = new EepromClass();

byte currentActionIndex;
const byte noOfactions = 8;
Action* actions[noOfactions];

void initializeActions() {
    actions[0] = new Wellcome(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[1] = new Menu(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[2] = new Play(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[3] = new HowToPlay(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[4] = new HallOfFame(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[5] = new Settings(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[6] = new About(lcd, joystick, gameMap, buzzer, eepromObj);
    actions[7] = new Register(lcd, joystick, gameMap, buzzer, eepromObj);
}

void setup() {
    lcd->initSetup();
    joystick->initSetup();
    gameMap->initSetup();
    // buzzer->initSetup();

    initializeActions();
        
    // currentActionIndex = 0; // Wellcome
    currentActionIndex = 2; // Play for debugging
    Serial.begin(9600);
}

void loop() {
    ActionIndex nextActionIndex = actions[currentActionIndex]->run();
    currentActionIndex = int(nextActionIndex);
}