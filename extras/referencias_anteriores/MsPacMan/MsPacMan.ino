#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"
#include "DirectionController.h"

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;
CommunicationManager* communicationManager;
DirectionController* directionController;


void setup() {
	Serial.begin(9600);

	//Communication Manager
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();

	//Line tracker
	lineTracker = new LineTracker();
	lineTracker->Init();
	communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
	communicationManager->WaitApproval();
	

	//Gyroscope Controller
	gyroscopeController = new GyroscopeController();
	gyroscopeController->Init();
	communicationManager->SendMsg(GYROSCOPE_INITIALIZED);
	communicationManager->WaitApproval();

	//Direccion Controller
	directionController = new DirectionController();
	
	//Motors Controller
	motorsController = new MotorsController();
	motorsController->SetLineTracker(lineTracker);
	motorsController->SetGyroscopeController(gyroscopeController);
	motorsController->SetDirectionController(directionController);
	motorsController->SetCommunicationManager(communicationManager);
	motorsController->Init();
	communicationManager->SendMsg(MOTORS_INITIALIZED);
	communicationManager->WaitApproval();


	communicationManager->SetDirectionController(directionController);
	communicationManager->SendMsg(DIRECCTION_INITIALIZED);
	communicationManager->WaitApproval();

	//Esperamos a la orden de empezar a jugar
	communicationManager->WaitForMsg(MESSAGE::START);
	communicationManager->SendMsg(MESSAGE::GREEN_LED);
	motorsController->Start();
}


void loop() {
	lineTracker->Update();
	gyroscopeController->Update();
	motorsController->Update();
	communicationManager->Update();	
}