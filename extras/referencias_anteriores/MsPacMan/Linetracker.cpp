#include "LineTracker.h"

LineTracker::LineTracker(){
	currentAction = lost;
}


/**
 * @brief Inicializa las pines del Arduino
 */
void LineTracker::Init(){
	pinMode(SENSOR_L, INPUT);
	pinMode(SENSOR_C, INPUT);
	pinMode(SENSOR_R, INPUT);
}


/**
 * @brief lee los sensores y establece que acción hay que relizar segun los datos leidos
 */
void LineTracker::Update(){
	int _left = digitalRead(SENSOR_L);
	int _center = digitalRead(SENSOR_C);
	int _right = digitalRead(SENSOR_R);

	if(_left == LINE && _center == CORRIDOR && _right == LINE) //recto
		currentAction = Action::straight;
	else if (_left == CORRIDOR && (_right == LINE || _center == LINE))  //desvio derecha
		currentAction = Action::leftCorrection;
	else if((_left == LINE || _center == LINE) && _right == CORRIDOR) //desvio izquierda
		currentAction = Action::rightCorrection;      
	else if(_left == LINE && _center == LINE && _right == LINE) //interseccion
		currentAction = Action::turn;
	else
		currentAction = Action::lost;
}


/**
 * @brief Devuelve la acción que debería hacer el robot en un determinado instante
 * 
 * @return Acción a realizar
 */
Action LineTracker::GetCurrentAction(){
	return currentAction;
}