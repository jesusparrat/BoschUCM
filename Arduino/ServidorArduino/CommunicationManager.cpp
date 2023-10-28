#include "CommunicationManager.h"

//pines para la led rgb
int red = 6;
int green = 5;
int blue = 3;

void rojo() {
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);
}

void azul() {
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 255);
}

void amarillo(){
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 0);   
}

void cian(){
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 255);   
}

void magenta(){
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 255);     
}

void blanco(){
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 255);     
}

void verde() {
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 0);
}

void nada() {
  analogWrite(red, 1);
  analogWrite(green, 1);
  analogWrite(blue, 1);
}

CommunicationManager::CommunicationManager(): miBT(10,11)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
    Serial.println("CommunicationManager::Init()");
}


/**
 * @brief Sincroniza el servidor arduino con el robot mediante la espera de confirmación 
 * de sincronización correcta 
 */
void CommunicationManager::Sync(){
//	while(!miBT.available() != 0)	{
//       Serial.println("Esperando conexión BT");
//       delay(100);
//  }
//	
	
	while(true){
		if(miBT.available() != 0){
			MESSAGE msg = ReadMsg();
			if(msg == SYNC){	
				break;		
			}
		}
      Serial.println("enviando SYNC_ATTEMP");
  		SendMsg(SYNC_ATTEMP);
  		delay(100);
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
