#include "MotorsController.h"
#include "LineTracker.h"


MotorsController::MotorsController(){

}

void MotorsController::Init(){
	pinMode(rightSpeed, OUTPUT);
	pinMode(forwardRight, OUTPUT);
	pinMode(backwardRight, OUTPUT);
	pinMode(forwardLeft, OUTPUT);
	pinMode(backwardLeft, OUTPUT);
	pinMode(leftSpeed, OUTPUT);

    digitalWrite(forwardLeft, HIGH);
    digitalWrite(backwardLeft, LOW);
    digitalWrite(forwardRight, LOW);
    digitalWrite(backwardRight, HIGH);

    analogWrite(rightSpeed, NORMAL_SPEED);
	analogWrite(leftSpeed, NORMAL_SPEED);
}


void MotorsController::Update(){
    Action action = lineTracker->GetCurrentAction();

    if(action == Action::straight){
        analogWrite(rightSpeed, NORMAL_SPEED);
        analogWrite(leftSpeed, NORMAL_SPEED);
        Serial.println("Recto");
    }
    else if(action == Action::rightCorrection){
        analogWrite(rightSpeed, REDUCED_SPEED);
        analogWrite(leftSpeed, INCREASED_SPEED);
        Serial.println("Left");
    }
    else if(action == Action::leftCorrection){
        analogWrite(rightSpeed, INCREASED_SPEED);
        analogWrite(leftSpeed, REDUCED_SPEED);
        Serial.println("Right");
    }
    else if (action == Action::lost){
        analogWrite(rightSpeed, 0);
        analogWrite(leftSpeed, 0);
    }
}

void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}