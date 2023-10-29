#include "MotorsController.h"
#include "LineTracker.h"
#include "DirectionController.h"
#include "CommunicationManager.h"

LineTracker* lineTracker;
MotorsController* motorsController;
DirectionController* directionController;
CommunicationManager* communicationManager;

void setup() {
    Serial.begin(9600);

	//Communication Manager
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();

    lineTracker = new LineTracker();
    lineTracker->Init();
	communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
	communicationManager->WaitApproval();

    directionController = new DirectionController();
	directionController->SetCommunicationManager(communicationManager);
	communicationManager->SetDirectionController(directionController);

    motorsController = new MotorsController();
    motorsController->Init();
    motorsController->SetLineTracker(lineTracker);
    motorsController->SetDirectionController(directionController);
	motorsController->SetCommunicationManager(communicationManager);

	communicationManager->SetMotorsController(motorsController);
	communicationManager->SendMsg(MOTORS_INITIALIZED);
	communicationManager->WaitApproval();
	communicationManager->SendMsg(DIRECCTION_INITIALIZED);
	communicationManager->WaitApproval();

	communicationManager->WaitForMsg(MESSAGE::START);
	motorsController->Start();
}




void loop() {
	communicationManager->Update();
    lineTracker->Update();
    motorsController->Update();
}