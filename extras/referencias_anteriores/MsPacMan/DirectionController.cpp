#include "DirectionController.h"
#include "MotorsController.h"

DirectionController::DirectionController(){
    currentInstruction = 0;
}

/**
 * @brief Devuelve la siguiente órden que tiene que seguir el robot al llegar a la siguiente intersección
 * 
 * @return Proxima dirección a la que se tiene que ir en la siguiente intersección
 */
TurningDirection DirectionController::GetNextDirection(){
    TurningDirection aux = turningDirections[currentInstruction];
    currentInstruction = (currentInstruction + 1) % INSTRUCTIONS_COUNT;
    return aux;
}