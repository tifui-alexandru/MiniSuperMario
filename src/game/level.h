#ifndef LEVEL_H
#define LEVEL_H
	
#include "camera_view.h"

class Level  {
	int time = 1000; // in seconds
    int id;

    byte newColumnsArray[7] = {
        B00001111,
        B00000001,
        B00000001,
        B00000001,
        B00000000,
        B00000000,
        B11111111
    };

    CameraView initialView;

public:
    Level() {};
    CameraView getInitialView() { return initialView; };
};

#endif