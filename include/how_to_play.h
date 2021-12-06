#ifndef HOW_TO_PLAY_H
#define HOW_TO_PLAY_H

#include <Arduino.h>
#include "action.h"

class HowToPlay : public Action {
public:
    HowToPlay();
    ActionIndex run() override;
};

#endif