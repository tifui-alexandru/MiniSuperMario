#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H

#include <Arduino.h>
#include "action.h"

class HallOfFame : public Action {
public:
    HallOfFame();
    ActionIndex run() override;
};

#endif