#pragma once
#include "TurningDirecction.h"

#define INSTRUCTIONS_COUNT 10

class DirectionController{
private:
	//recorrido provisional
	TurningDirection turningDirections[INSTRUCTIONS_COUNT] = {
		TurningDirection::right, TurningDirection::none,
		TurningDirection::right, TurningDirection::left,
		TurningDirection::right, TurningDirection::right,
		TurningDirection::none, TurningDirection::none,
		TurningDirection::none, TurningDirection::right
	};

	int currentInstruction;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};