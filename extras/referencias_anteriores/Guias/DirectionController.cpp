#include "DirectionController.h"
#include "MotorsController.h"
#include "CommunicationManager.h"

DirectionController::DirectionController(){
    nextIntersecction = right;
}


void DirectionController::AddIntersection(TurningDirection direction){
    //communicationManager->SendMsg(MESSAGE::MAGENTA_LED);
    nextIntersecction = direction;
}


/**
 * @brief Devuelve la siguiente órden que tiene que seguir el robot al llegar a la siguiente intersección
 * 
 * @return Proxima dirección a la que se tiene que ir en la siguiente intersección
 */
TurningDirection DirectionController::GetNextDirection(){
    return nextIntersecction;
}


void DirectionController::SetCommunicationManager(CommunicationManager* comMng){
    communicationManager = comMng;
}