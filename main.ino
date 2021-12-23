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
#include "src/components/utils.h"

Lcd* lcd = new Lcd();
Joystick* joystick = new Joystick();
Matrix* gameMap = new Matrix();
Buzzer* buzzer = new Buzzer();
EepromClass* eepromObj = new EepromClass();
Utils* gameUtils = new Utils();

ActionIndex currentActionIndex;
const byte noOfactions = 8;

Action* action;

void setup() {
    eepromObj->initSetup();
    lcd->initSetup(eepromObj);
    joystick->initSetup();
    gameMap->initSetup(eepromObj);

    randomSeed(analogRead(0));

    currentActionIndex = wellcomeActionIndex;
    action = new Wellcome(lcd, joystick, gameMap, buzzer, eepromObj);

    // currentActionIndex = playActionIndex; // for debugging
    // action = new Play(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);

    // currentActionIndex = menuActionIndex; // for debugging
    // action = new Menu(lcd, joystick, gameMap, buzzer, eepromObj);

    Serial.begin(9600);
}

void loop() {
    buzzer->playSound(gameUtils->soundsState);

    ActionIndex nextActionIndex = action->run();

    if (currentActionIndex != nextActionIndex) {
        currentActionIndex = nextActionIndex;

        delete action;

        if (currentActionIndex == wellcomeActionIndex)
            action = new Wellcome(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == menuActionIndex)
            action = new Menu(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == playActionIndex)
            action = new Play(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == howToPlayActionIndex)
            action = new HowToPlay(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == hallOfFameActionIndex)
            action = new HallOfFame(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == settingsActionIndex)
            action = new Settings(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == aboutActionIndex)
            action = new About(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
        else if (currentActionIndex == registerActionIndex)
            action = new Register(lcd, joystick, gameMap, buzzer, eepromObj, gameUtils);
    }
}