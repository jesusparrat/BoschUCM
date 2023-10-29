#pragma once
#include "TurningDirecction.h"

#define INSTRUCTIONS_COUNT_MAX 10

class CommunicationManager;

class DirectionController{
private:
	CommunicationManager* communicationManager;

	TurningDirection nextIntersecction;

public:
	DirectionController();

	void AddIntersection(TurningDirection direction);

	TurningDirection GetNextDirection();

	void SetCommunicationManager(CommunicationManager* comMng);
};