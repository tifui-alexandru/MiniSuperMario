#ifndef ABOUT_H
#define ABOUT_H

#include <Arduino.h>
#include "action.h"

class About : public Action {
public:
    About();
    ActionIndex run() override;
};

#endif