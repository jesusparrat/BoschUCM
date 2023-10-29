#include "MotorsController.h"
#include "LineTracker.h"
#include "DirectionController.h"
#include "TurningDirecction.h"
#include "CommunicationManager.h"

#define TURN_INTERSECCTION_MIN_TIME 250

MotorsController::MotorsController(){

}

void MotorsController::Init(){
	pinMode(rightSpeed, OUTPUT);
	pinMode(forwardRight, OUTPUT);
	pinMode(backwardRight, OUTPUT);
	pinMode(forwardLeft, OUTPUT);
	pinMode(backwardLeft, OUTPUT);
	pinMode(leftSpeed, OUTPUT);

	digitalWrite(forwardLeft, LOW);
	digitalWrite(backwardLeft, LOW);
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, LOW);

	analogWrite(rightSpeed, NORMAL_SPEED);
	analogWrite(leftSpeed, NORMAL_SPEED);

	endIntersecctionTime = -TURN_INTERSECCTION_MIN_TIME;
	currentState = STRAIGHT;
}

void MotorsController::Start(){
	digitalWrite(forwardLeft, HIGH);
	digitalWrite(backwardLeft, LOW);
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, HIGH);
}

void MotorsController::Update(){

	switch (currentState)
	{
	case STRAIGHT:
		Straight();
		break;
	case TURN:
		Turn();
		break;
	default:
		break;
	}
}



void MotorsController::Straight(){
	// //aún podríamos estar en la zona de detección
	// if(millis() - endIntersecctionTime < TURN_INTERSECCTION_MIN_TIME)
	// 	return;

	if(lineTracker->StartTurn())
	{
		//TODO aquí deberemos sacar la dirección hacia la que queremos girar
		TurningDirection turn = directionController->GetNextDirection();

		if(turn == TurningDirection::right){
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, REDUCED_SPEED);
		}
		else if(turn == TurningDirection::left)
		{
			analogWrite(rightSpeed, INCREASED_SPEED);
			analogWrite(leftSpeed, REDUCED_SPEED);
		}
		

		startIntersecctionTime = millis();
		currentState = TURN;
	}
}


void MotorsController::Turn(){
	//aún podríamos estar en la zona de detección
	// if(millis() - startIntersecctionTime < TURN_INTERSECCTION_MIN_TIME)
	// 	return;

	if(lineTracker->EndTurn())
	{
		analogWrite(rightSpeed, 0);
		analogWrite(leftSpeed, 0);

		endIntersecctionTime = millis();
		currentState = STRAIGHT;
		communicationManager->SendMsg(MESSAGE::TURN_ENDED);
	}
}



void MotorsController::Walk(){
	analogWrite(rightSpeed, NORMAL_SPEED);
	analogWrite(leftSpeed, NORMAL_SPEED);
}

void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}

void MotorsController::SetDirectionController(DirectionController* _directionController){
	directionController = _directionController;
}

void MotorsController::SetCommunicationManager(CommunicationManager* _communicationManager){
	communicationManager = _communicationManager;
}