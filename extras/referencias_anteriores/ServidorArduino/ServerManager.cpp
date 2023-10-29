#include "ServerManager.h"

ServerManager::ServerManager(){
}

/**
 * @brief Sincroniza el servidor arduino con el programa en Java donde corre
 * el simulador MsPacMan 
 */
void ServerManager::SyncToJava(){
    while(true){
		if(Serial.available()){
			JAVA_MESSAGE msg = ReadMsg();
            if(msg == JAVA_SYNC_ATTEMP){
				SendMsg(JAVA_SYNC);
				break;
			}
		}

		delay(5);
	}
}

/**
 * @brief Envia un mensaje al programa de Java
 * 
 * @param msg Mensaje a enviar
 */
void ServerManager::SendMsg(JAVA_MESSAGE msg){
    Serial.flush();
    Serial.write((int)msg);
    Serial.flush();
}

/**
 * @brief Lee un mensaje que viene desde el programa en java
 * 
 * @return Mensaje recibido
 */
JAVA_MESSAGE ServerManager::ReadMsg(){
    JAVA_MESSAGE msg = (JAVA_MESSAGE)Serial.read();
    return msg;
}


/**
 * @brief Esperamos hasta recibir un mensaje en concreto. Todos los mensajes
 * que se reciban que no sean el esperado serán ignorados * 
 * 
 * @param msg Mensaje esperado
 */
void ServerManager::WaitForMsg(JAVA_MESSAGE msg){
	while(true){
		if(Serial.available() && ReadMsg() == msg){
			break;
		}
		delay(5);
	}
}