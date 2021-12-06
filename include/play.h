#ifndef PLAY_H
#define PLAY_H

#include <Arduino.h>
#include "action.h"

class Play : public Action {
public:
    Play() {}
    ActionIndex run() override;
};

#endif