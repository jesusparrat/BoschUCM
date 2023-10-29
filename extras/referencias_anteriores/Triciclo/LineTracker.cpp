#include "LineTracker.h"

LineTracker::LineTracker(){
	currentAction = straight;
}

void LineTracker::Init(){
	pinMode(SENSOR_L, INPUT);
	pinMode(SENSOR_R, INPUT);
}


void LineTracker::Update(){
	int _left = digitalRead(SENSOR_L);
	int _right = digitalRead(SENSOR_R);

	if(_left == BLANK && _right == BLANK) //recto
		currentAction = Action::straight;
	else if (_left == LINE )  //desvio derecha
		currentAction = Action::leftCorrection;
	else if(_right == LINE) //desvio izquierda
		currentAction = Action::rightCorrection;     
	else 
		currentAction = Action::lost; 
}

/**
 * @brief Devuelve la acción que debería hacer el robot en un determinado instante
 * 
 * @return Acción 
 */
Action LineTracker::GetCurrentAction(){
	return currentAction;
}