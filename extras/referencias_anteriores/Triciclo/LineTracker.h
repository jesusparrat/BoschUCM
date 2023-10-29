#pragma once
#include <Arduino.h>

enum Action{
    straight, 
	leftCorrection,
	rightCorrection,
    lost
};


#define LINE 1
#define BLANK 0

class LineTracker{
private:

	int SENSOR_L = 6;
	int SENSOR_R = 5;

    Action currentAction;
public:

    LineTracker();

    void Init();
    void Update();

    Action GetCurrentAction();
};