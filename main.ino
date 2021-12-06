#include "include/menu.h"
#include "include/wellcome.h"
#include "include/play.h"
#include "include/how_to_play.h"
#include "include/hall_of_fame.h"
#include "include/settings.h"
#include "include/about.h"
#include "include/utils.h"

byte currentActionIndex;
const byte noOfactions = 2;
Action *actions[noOfactions] = {
    new Wellcome(),
    new Menu(),
    // new Play(),
    // new HowToPlay(),
    // new HallOfFame(),
    // new Settings(),
    // new About()
};

void setup() {
    for (byte i = 0; i < noOfactions; ++i) 
        actions[i]->initSetup();
    currentActionIndex = 0;
}

void loop() {
    ActionIndex nextActionIndex = actions[currentActionIndex]->run();
    currentActionIndex = int(nextActionIndex);
}
