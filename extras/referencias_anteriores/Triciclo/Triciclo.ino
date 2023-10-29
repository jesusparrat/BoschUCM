#include "MotorsController.h"
#include "LineTracker.h"


LineTracker* lineTracker;
MotorsController* motorsController;


void setup() {
    Serial.begin(9600);
    Serial.println("Hola");

    lineTracker = new LineTracker();
    lineTracker->Init();

    motorsController = new MotorsController();
    motorsController->Init();
    motorsController->SetLineTracker(lineTracker);
}



void loop() {
    lineTracker->Update();
    motorsController->Update();
}