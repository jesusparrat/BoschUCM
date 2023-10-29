#pragma once
#include <Arduino.h>

#define NORMAL_SPEED 70.0
#define REDUCED_SPEED 50.0
#define INCREASED_SPEED 90.0


class LineTracker;


class MotorsController{
private:
	int rightSpeed = 11;
	int backwardRight = A0;
	int forwardRight = A1;
	int backwardLeft = A2;
	int forwardLeft = A3;
	int leftSpeed = 10;

	LineTracker* lineTracker;

public:
	MotorsController();

	void Init();
	void Update();


	void SetLineTracker(LineTracker* _lineTracker);
};