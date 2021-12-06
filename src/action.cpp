#include "../include/action.h"

Action::Action() {
    lcd = new Lcd();
    matrix = new Matrix();
}

void Action::initSetup() {
    lcd->initSetup();
    matrix->initSetup();
}