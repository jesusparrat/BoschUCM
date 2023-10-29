#include "LineTracker.h"

LineTracker::LineTracker(){
}

void LineTracker::Init(){
	pinMode(START_SENSOR, INPUT);
}


void LineTracker::Update(){
	leftLine = false;
	
	if(digitalRead(START_SENSOR) == BLACK && previousLeftLine == false){
		leftLine = true;
		previousLeftLine = true;
	}
	else if (digitalRead(START_SENSOR) != BLACK)
	{
		previousLeftLine = false;
	}
}

/**
 * @brief Devuelve si la linea de abajo del lado izquierdo del robot es negra o no
 * 
 * @return Color 
 */
bool LineTracker::StartTurn(){
	return leftLine;
}

/**
 * @brief Devuelve si la linea de abajo del lado derecho robot es negra o no
 * 
 * @return Color 
 */
bool LineTracker::EndTurn(){
	return leftLine;
}