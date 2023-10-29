#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(5,6)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
}


/**
 * @brief Sincroniza el servidor arduino con el robot mediante la espera de confirmación 
 * de sincronización correcta 
 */
void CommunicationManager::Sync(){
	while(true){
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == SYNC){	
				break;		
			}
		}
		
		SendMsg(SYNC_ATTEMP);

		delay(5);
	}
}

/**
 * @brief Envia un mensaje via bluetooth
 * Primero de todo se hace un flush por 
 * 
 * @param msg 
 */
void CommunicationManager::SendMsg(MESSAGE msg){
	miBT.flush();
	miBT.write((int)msg);
	miBT.flush();
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
 * @brief Lee un mensaje y lo devuelve
 * 
 * @return El mensaje leido
 */
MESSAGE CommunicationManager::ReadMsg(){
	MESSAGE msg = (MESSAGE)miBT.read();
	return msg;
}

/**
 * @brief Esperamos a que se reciban los mensajes de inicialización de cada componente
 * del robot 
 */
void CommunicationManager::WaitForRobotToInitialize(){
	WaitForMsg(LINE_TRACKER_INITIALIZED);
	Serial.println("Sensores Linea Inicializados");
	
	WaitForMsg(MOTORS_INITIALIZED);
	Serial.println("Motores Inicializados");

	WaitForMsg(DIRECCTION_INITIALIZED);
	Serial.println("Dirección Inicializada");
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
				SendMsg(OK);
				break;
			}
		}
		delay(5);
	}
}
