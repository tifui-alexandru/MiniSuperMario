#ifndef WELLCOME_H
#define WELLCOME_H

#include <Arduino.h>
#include "action.h"

class Wellcome : public Action {
    char* msgLine1 = "Welcome to";
    char* msgLine2 = "Mini Super Mario!";
    unsigned int startTime;
    const unsigned int interval = 5000;

public:
    Wellcome();
    ActionIndex run() override;
};

#endif