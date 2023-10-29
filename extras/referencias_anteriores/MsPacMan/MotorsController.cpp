#include "MotorsController.h"
#include "LineTracker.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"
#include "DirectionController.h"

MotorsController::MotorsController(){
	state = followingLine;
	turningDirection = none;
	perfectAngle = 0;
}

/**
 * @brief Inicializa los pines del Arduino
 */
void MotorsController::Init(){
	pinMode(rightSpeed, OUTPUT);
	pinMode(forwardRight, OUTPUT);
	pinMode(backwardRight, OUTPUT);
	pinMode(forwardLeft, OUTPUT);
	pinMode(backwardLeft, OUTPUT);
	pinMode(leftSpeed, OUTPUT);

	Stop();
}


/**
 * @brief empieza el movimiento del robot 
 */
void MotorsController::Start(){
	Stright(true);

	nextDirection = directionController->GetNextDirection();
	timeSinceLastTurn = millis();
}


/**
 * @brief Realiza la acción correspondiente según en que estado se encuentre
 */
void MotorsController::Update(){
	switch (state)
	{
	case followingLine:
		FollowLine();
		break;
	case turning:
		Turning();
		break;
	case turnExit:
		TurnExit();
		break;
	case followGyroscope:
		FollowGyroscope();
		break;
		break;
	default:
		break;
	}
}


/**
 * @brief Método encargado de dirigir el robot cuando se va en linea recta.
 * Se encarga de leer la acción que tiene que realizar dada por el lineTracker.
 * Encargado de detectar cuando se tiene que empezar a girar.
 */
void MotorsController::FollowLine(){
	Action currentAction = lineTracker->GetCurrentAction();
	
	if(currentAction == Action::straight){ //recto		
		Stright(true);
	}
	else if(currentAction == turn){ //Giro 90 grados
		timeReachedIntersecction = millis();

		if(nextDirection == TurningDirection::left){
			turningDirection = left;
			NinetyGegreeTurn();
		}
		else if (nextDirection == TurningDirection::right){
			turningDirection = right;
			NinetyGegreeTurn();
		}
		else{
			nextDirection = directionController->GetNextDirection();
			Stright(true);	
			state = followGyroscope;			

			if(communicationManager != nullptr)
				communicationManager->SendMsg(MESSAGE::YELLOW_LED);
		}
	}
	else if (currentAction == leftCorrection) { //desvio derecha
		Stright(true);

		analogWrite(leftSpeed, REDUCED_SPEED);
		analogWrite(rightSpeed, INCREASED_SPEED);
	}
	else if(currentAction == rightCorrection){ //desvio izquierda
		Stright(true);

		analogWrite(leftSpeed, INCREASED_SPEED);
		analogWrite(rightSpeed, REDUCED_SPEED);
		
	}
	else if (currentAction == lost){ //parada
		Stop();
	}
}

/**
 * @brief Controla el giro, encargado de pararlo cuando es necesario 
 */
void MotorsController::Turning(){
	if(CurrentDirectionOffset() < TURNING_DEGREES_BUFFER &&
	millis() - timeReachedIntersecction > 100){ //para que si entra pasado, no detecte giro al pasar por el punto medio
		turningDirection = (turningDirection == right) ? left: right;
		Turn();
		delay(35);
		turningDirection = none;

		Stop();
		delay(200);
		Stright(true);	
		state = turnExit;
		timeExitIntersecction = millis();
		gyroscopeController->ResetYaw();
	}
}

/**
 * @brief Encargado de dirigir el robot los instantes posteriores a un giro
 * Encargado tambien de sobrecorregirlo para salir en la dirección correcta
 */
void MotorsController::TurnExit(){	
	Stright(true);
	
	if(CurrentDirectionOffset() < EXIT_TURN_BUFFER){ //si está alineado
		if(millis() - timeExitIntersecction > MINIMUM_EXIT_TURN_TIME)
		{
			if(communicationManager != nullptr)
				communicationManager->SendMsg(MESSAGE::GREEN_LED);
			state = followingLine;
			timeSinceLastTurn = millis();
			nextDirection = directionController->GetNextDirection(); 
			analogWrite(rightSpeed, NORMAL_SPEED);
			analogWrite(leftSpeed, NORMAL_SPEED);
		}
		else {
			//Si esta en linea pero aun no ha pasado suficiente tiempo mínimo, se
			//acelera más rápido para recuperar la velocidad de crucero 
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, INCREASED_SPEED);  
		}
	}
	else{
		TurningDirection overCorrectionDir = OverCorrectionDirection();
		AplyOverCorrection(overCorrectionDir);
	}
}


/**
 * @brief Encargado de dirigir el robot guiandose únicamente por los datos 
 * recibidos por el giroscopio 
 */
void MotorsController::FollowGyroscope(){
	if(CurrentDirectionOffset() >= TURNING_DEGREES_BUFFER){
		TurningDirection overCorrectionDir = OverCorrectionDirection();
		AplyOverCorrection(overCorrectionDir);
	}

	
	//hemos salido de la zona de la interseccion (zona negra) y los sensores ya detectan
	//los carriles. Ya se puede volver al control normal
	if(millis() - timeReachedIntersecction > MINIMUM_EXIT_TURN_TIME){
		state = followingLine;
		if(communicationManager != nullptr)
			communicationManager->SendMsg(MESSAGE::GREEN_LED);
	}
}


/**
 * @brief Establece los motores para ir en linea recta
 * 
 * @param forwards true si se quiere de frente, false en caso de querer ir marcha atrás
 */
void MotorsController::Stright(bool forwards){
	if(forwards){
		digitalWrite(forwardLeft, LOW);
		digitalWrite(backwardLeft, HIGH);
		digitalWrite(forwardRight, HIGH);
		digitalWrite(backwardRight, LOW);
	}
	else {
		digitalWrite(forwardLeft, HIGH);
		digitalWrite(backwardLeft, LOW);
		digitalWrite(forwardRight, LOW);
		digitalWrite(backwardRight, HIGH);
	}


	analogWrite(rightSpeed, NORMAL_SPEED);
	analogWrite(leftSpeed, NORMAL_SPEED);
}



/**
 * @brief Calcual el tiempo en ms necesario de frenado para el tiempo que lleva acelerando
 * 
 * @return tiempo en ms que tiene que estar frenando al llegar a una intersección
 */
int MotorsController::GetBrakingTime(){
	if(millis() - timeSinceLastTurn > MIN_TIME_FOR_FULL_BRAKE){
		return FULL_BRAKE_TIME;
	}
	else{
		return ((millis() - timeSinceLastTurn) * FULL_BRAKE_TIME) / MIN_TIME_FOR_FULL_BRAKE;
	}
	return FULL_BRAKE_TIME;
}


/**
 * @brief Para los motores 
 */
void MotorsController::Stop(){
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, LOW);
	digitalWrite(forwardLeft, LOW);
	digitalWrite(backwardLeft, LOW);
}


/**
 * @brief Empieza a realizar un giro de 90 grados
 */
void MotorsController::NinetyGegreeTurn(){	
	if(communicationManager != nullptr)
		communicationManager->SendMsg(MESSAGE::RED_LED);
	
	Stop();
	delay(300);

	state = turning;
	
	if(turningDirection == TurningDirection::left)
		perfectAngle += 270;
	else if(turningDirection == TurningDirection::right)
		perfectAngle += 90;

	perfectAngle = perfectAngle % 360;
	gyroscopeController->SetTargetYaw(perfectAngle);
	Turn();
}


/**
 * @brief Establece los motores en direcciones inversas para realizar un giro
 */
void MotorsController::Turn(){
	if(turningDirection == right){
		digitalWrite(forwardLeft, LOW);
		digitalWrite(backwardLeft, HIGH);
		digitalWrite(forwardRight, LOW);
		digitalWrite(backwardRight, HIGH);
	}
	else {
		digitalWrite(forwardLeft, HIGH);
		digitalWrite(backwardLeft, LOW);
		digitalWrite(forwardRight, HIGH);
		digitalWrite(backwardRight, LOW);
	}

	analogWrite(leftSpeed, NORMAL_SPEED);
	analogWrite(rightSpeed, NORMAL_SPEED);
}


/**
 * @brief Devuelve en grados positivos, la desviacion de la trayectorio del robot
 * en un determinado instante respecto la direccion que debería tener (perfectAngle) 
 * @return desviacion en grados positivos
 */
float MotorsController::CurrentDirectionOffset(){
	if(perfectAngle == 0){
		if(gyroscopeController->GetCurrentYaw() < 180)
			return gyroscopeController->GetCurrentYaw();
		else
			return 360 - gyroscopeController->GetCurrentYaw();
	}
	else
		return abs(gyroscopeController->GetCurrentYaw() - perfectAngle);	
}


/**
 * @brief Devuelve la dirección hacia la que el robot tiene que sobre-corregir tras realizar un giro de 90 grados * 
 * @return Dirección hacia la que se tiene que corregir 
 */
TurningDirection MotorsController::OverCorrectionDirection(){
	float aux = gyroscopeController->GetCurrentYaw(); 

	if(perfectAngle == 0){
		if(aux < 180)
			return left;
		else
			return right;
	}
	else{
		if(aux < perfectAngle)
			return right;
		else 
			return left;
	}
}


/**
 * @brief Cambia las velocidades de los motores para realizar la sobrecorrección necesaria
 * 
 * @param dir dirección a la que tenemos que sobrecorregir
 */
void MotorsController::AplyOverCorrection(TurningDirection dir){
	Stright(true);

	if(dir == left){
		analogWrite(leftSpeed, REDUCED_SPEED * 0.8f);
		analogWrite(rightSpeed, INCREASED_SPEED * 1.2f);
	}
	else if (dir == right){
		analogWrite(leftSpeed, INCREASED_SPEED * 1.2f);
		analogWrite(rightSpeed, REDUCED_SPEED * 0.8f);
	}
}


void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}

void MotorsController::SetGyroscopeController(GyroscopeController* _gyroscopeController){
	gyroscopeController = _gyroscopeController;
}

void MotorsController::SetCommunicationManager(CommunicationManager* _communicationManager){
	communicationManager = _communicationManager;
}

void MotorsController::SetDirectionController(DirectionController* _directionController){
	directionController = _directionController;
}