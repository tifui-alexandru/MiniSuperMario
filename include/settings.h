#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include "action.h"

class Settings : public Action {
public:
    Settings();
    ActionIndex run() override;
};

#endif