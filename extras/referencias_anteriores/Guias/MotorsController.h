#pragma once
#include <Arduino.h>
#include "States.h"

#define NORMAL_SPEED 120.0
#define REDUCED_SPEED 40.0
#define INCREASED_SPEED 255.0


class LineTracker;
class DirectionController;
class CommunicationManager;


class MotorsController{
private:
	int rightSpeed = 11;
	int backwardRight = A0;
	int forwardRight = A1;
	int backwardLeft = A2;
	int forwardLeft = A3;
	int leftSpeed = 10;

	long startIntersecctionTime;
	long endIntersecctionTime;

	LineTracker* lineTracker;
	DirectionController* directionController;
	CommunicationManager* communicationManager;
	States currentState;

	void Straight();
	void Turn();

public:
	MotorsController();

	void Init();
	void Start();
	void Update();

	void Walk();


	void SetLineTracker(LineTracker* _lineTracker);
	void SetDirectionController(DirectionController* _directionController);
	void SetCommunicationManager(CommunicationManager* _communicationManager);
};