#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "CommunicationManager.h"
#include "ServerManager.h"

CommunicationManager* communicationManager;
ServerManager* serverManager;
JAVA_MESSAGE currentOrientation = JAVA_MESSAGE::PAC_MAN_LEFT;



/**
 * @brief Se inicializan todos los pines del Arduino 
 */
void Init(){
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Inicializando Servidor");

  nada();
}

void setup() {	
	Init();

    Serial.println("Arrancando CommunicationManager");
	//inicialización y sincronización de la comunicación con el robot
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();
	communicationManager->WaitForRobotToInitialize();

  azul();

	serverManager = new ServerManager();
	serverManager->SyncToJava();

  amarillo();

	serverManager->WaitForMsg(JAVA_MESSAGE::JAVA_START);
	communicationManager->SendMsg(MESSAGE::START);

  rojo();

  
}

//JAVA_MESSAGE currentOrientation = JAVA_MESSAGE::PAC_MAN_LEFT;

/**
 * @brief Se reciben y se procesan los mensajes del MsPacManEngine
 * Actualmente solo se imprimen por el monitor serial ya que el recorrido
 * es fijo para facilitar la depuración en el robot
 */
void MsPacManOrientationCommunication(){
	if(Serial.available()){
		JAVA_MESSAGE msg = serverManager->ReadMsg();
		MESSAGE msgToSend = MESSAGE::NONE;


		if(msg == PAC_MAN_UP){
			Serial.println("Up");
		
			if(currentOrientation == PAC_MAN_LEFT)
				msgToSend = RIGHT;
			else if(currentOrientation == PAC_MAN_RIGHT)
				msgToSend = LEFT;
      else if(currentOrientation == PAC_MAN_DOWN)
        msgToSend = TURN180;
      else if(currentOrientation == PAC_MAN_UP)
        msgToSend = NOSTOP;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_RIGHT){
			Serial.println("Right");

			if(currentOrientation == PAC_MAN_UP)
				msgToSend = RIGHT;
			else if(currentOrientation == PAC_MAN_DOWN)
				msgToSend = LEFT;
      else if(currentOrientation == PAC_MAN_LEFT)
        msgToSend = TURN180;
      else if(currentOrientation == PAC_MAN_RIGHT)
        msgToSend = NOSTOP;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_DOWN){
			Serial.println("Down");	

			if(currentOrientation == PAC_MAN_LEFT)
				msgToSend = LEFT;
			else if(currentOrientation == PAC_MAN_RIGHT)
				msgToSend = RIGHT;
      else if(currentOrientation == PAC_MAN_DOWN)
        msgToSend = NOSTOP;
      else if(currentOrientation == PAC_MAN_UP)
        msgToSend = TURN180;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_LEFT){
			Serial.println("Left");	

			if(currentOrientation == PAC_MAN_UP)
				msgToSend = LEFT;
			else if(currentOrientation == PAC_MAN_DOWN)
				msgToSend = RIGHT;
      else if(currentOrientation == PAC_MAN_LEFT)
        msgToSend = NOSTOP;
      else if(currentOrientation == PAC_MAN_RIGHT)
        msgToSend = TURN180;

			currentOrientation = msg;
		}
		

//		communicationManager->SendMsg(LEFT);
    
    communicationManager->SendMsg(msgToSend);
	}
}


/**
 * @brief Se lee y se procesan de los mensajes de debug recibidos desde el robot
 **/
void ReadMsg(){
	if(communicationManager->MsgAvailable()){
		Serial.println("Mensaje Recibido");
		MESSAGE msg = communicationManager->ReadMsg();

		if(msg == RED_LED){
			rojo();
		}
		else if(msg == BLUE_LED){
			azul();
		}
		else if(msg == YELLOW_LED){
	    amarillo();
		}
		else if(msg == CIAN_LED){
			cian();	
		}
		else if(msg == MAGENTA_LED){
			magenta();	
		}
		else if(msg == WHITE_LED){
			blanco();
		}
		else if(msg == GREEN_LED){
			verde();
		}
		else if(msg == TURN_ENDED){
			serverManager->SendMsg(JAVA_MESSAGE::JAVA_TURN_ENDED);
		}
	}
}

void loop() {
  
	MsPacManOrientationCommunication();

	ReadMsg();
  
}
