#pragma once

#include <Arduino.h>

#define LINE 1
#define CORRIDOR 0

enum Action {
	straight, 
	leftCorrection,
	rightCorrection,
	hardLeftCorrection,
	hardRightCorrection, 
	turn,
	lost
};


class LineTracker{
private:
	int SENSOR_L = 7;
	int SENSOR_C = 6;
	int SENSOR_R = 5;

	Action currentAction; //action that needs to take place acorging to the readings from the sensor

public:
	LineTracker();

	void Init();
	void Update();

	Action GetCurrentAction();
};
