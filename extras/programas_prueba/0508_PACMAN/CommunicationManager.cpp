#include "CommunicationManager.h"
//#include "DirectionController.h"
//#include "MotorsController.h"


CommunicationManager::CommunicationManager(){}

void CommunicationManager::Init(){
	Serial3.begin(9600); //establece frecuencia de comunicación
  Serial.println("CommunicationManager::Init()");
}

/**
 * @brief Sincroniza el robot con el servidor arduino.
 * Todo mensaje recibido que no se SYNC_ATTEMP será ignorad y perdido
 */
void CommunicationManager::Sync(){
	Serial.println("intentando sincronizar");
	
	// esperamos hasta recibir el mensaje de sincronicación
	while(true){
		if(Serial3.available() != 0){
      Serial.println("estoy aqui");
			MESSAGE msg = ReadMsg();
			if(msg == SYNC_ATTEMP){
				SendMsg(SYNC);
				Serial.println("Sincronizados");
				break;
			}
		}
	}
}

/**
 * @brief Envía un mensaje al servidor arduino
 * 
 * @param msg Mensaje a enviar
 */
void CommunicationManager::SendMsg(MESSAGE msg){
	Serial3.flush();
	Serial3.write((int)msg);
	Serial3.flush();
}

/**
 * @brief Lee un mensaje del servidor arduino
 * 
 * @return Mensaje leido
 */
MESSAGE CommunicationManager::ReadMsg(){
	MESSAGE msg = (MESSAGE)Serial3.read();
	return msg;
}


/**
 * @brief Revisa si hay un mensaje disponible
 * 
 * @return true si hay un mensaje disponible
 * @return false si no hay un mensaje disponible
 */
bool CommunicationManager::MsgAvailable(){
	return Serial3.available();
}


/**
 * @brief Espera a un mensaje de confirmación indicando que el servidor arduino
 * ha recibido correctamente un mensaje 
 */
void CommunicationManager::WaitApproval(){
	while(true){
		if(Serial3.available()){
			MESSAGE msg = ReadMsg();
			if(msg == OK){
				return;
			}
		}
		delay(5);
	}
}


void CommunicationManager::Update(){
	//Comentado provisionalmente ya que de momento el recorrido está establecido por defecto en el DirectionController

	if(Serial3.available()){
		MESSAGE msg = ReadMsg();
//		if(msg == LEFT){
//			directionController->AddIntersection(left);
//			motorsController->Walk();
//		}
//		else if(msg == NONE){
//			directionController->AddIntersection(none);		
//			motorsController->Walk();	
//		}
//		else if(msg == RIGHT){
//			directionController->AddIntersection(right);	
//			motorsController->Walk();		
//		}
	}
}

/**
 * @brief Esperamos hasta recibir un mensaje en concreto. Todos los mensajes
 * que se reciban que no sean el esperado serán ignorados * 
 * 
 * @param msg Mensaje esperado
 */
void CommunicationManager::WaitForMsg(MESSAGE msg){
	while (true)
	{
		if(Serial3.available()){
			MESSAGE msgAux = ReadMsg();
			if(msgAux == msg){
				break;
			}
		}
		delay(50);
	}
}

//void CommunicationManager::SetDirectionController(DirectionController* d){
//	directionController = d;
//}
//
//void CommunicationManager::SetMotorsController(MotorsController* m){
//	motorsController = m;
//}
