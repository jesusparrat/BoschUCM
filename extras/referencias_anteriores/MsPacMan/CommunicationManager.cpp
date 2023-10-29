#include "CommunicationManager.h"
#include "DirectionController.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600); //establece frecuéncia de comunicación
}

/**
 * @brief Sincroniza el robot con el servidor arduino.
 * Todo mensaje recibido que no se SYNC_ATTEMP será ignorad y perdido
 */
void CommunicationManager::Sync(){
	Serial.println("intentnado sincronizar");
	
	//esperamos hasta recibir el mensaje de sincronicación
	while(true){
		if(miBT.available()){
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
	miBT.flush();
	miBT.write((int)msg);
	miBT.flush();
}

/**
 * @brief Lee un mensaje del servidor arduino
 * 
 * @return Mensaje leido
 */
MESSAGE CommunicationManager::ReadMsg(){
	MESSAGE msg = (MESSAGE)miBT.read();
	return msg;
}


/**
 * @brief Revisa si hay un mensaje disponible
 * 
 * @return true si hay un mensaje disponible
 * @return false si no hay un mensaje disponible
 */
bool CommunicationManager::MsgAvailable(){
	return miBT.available();
}


/**
 * @brief Espera a un mensaje de confirmación indicando que el servidor arduino
 * ha recibido correctamente un mensaje 
 */
void CommunicationManager::WaitApproval(){
	while(true){
		if(miBT.available()){
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

	// if(miBT.available()){
	// 	MESSAGE msg = ReadMsg();
	// 	if(msg == OK){
	// 		return;
	// 	}
	// }
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
		if(miBT.available()){
			MESSAGE msgAux = ReadMsg();
			if(msgAux == msg){
				break;
			}
		}
		delay(50);
	}
}

void CommunicationManager::SetDirectionController(DirectionController* d){
	directionController = d;
}