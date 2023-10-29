#include "CommunicationManager.h"
#include "ServerManager.h"

CommunicationManager* communicationManager;
ServerManager* serverManager;

//pines para la led rgb
int red = 9;
int green = 10;
int blue = 11;


/**
 * @brief Se inicializan todos los pines del Arduino 
 */
void Init(){
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Inicializamos");

	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	
	analogWrite(red, 255);
	analogWrite(green, 0);
	analogWrite(blue, 0);
}

void setup() {	
	Init();

	//inicialización y sincronización de la comunicación con el robot
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();
	communicationManager->WaitForRobotToInitialize();


	analogWrite(red, 0);
	analogWrite(green, 0);
	analogWrite(blue, 255);


	serverManager = new ServerManager();
	serverManager->SyncToJava();


	serverManager->WaitForMsg(JAVA_MESSAGE::JAVA_START);
	communicationManager->SendMsg(MESSAGE::START);


	// analogWrite(red, 0);
	// analogWrite(green, 255);
	// analogWrite(blue, 0);
}

JAVA_MESSAGE currentOrientation = JAVA_MESSAGE::PAC_MAN_LEFT;

/**
 * @brief Se reciben y se procesan los mensajes del MsPacManEngine
 * Actualmente solo se imprimen por el monitor serial ya que el recorrido
 * es fijo para facilitar la depuración en el robot
 */
void MsPacManEngineCommunication(){
	if(Serial.available()){
		JAVA_MESSAGE msg = serverManager->ReadMsg();
		MESSAGE msgToSend = MESSAGE::NONE;


		if(msg == PAC_MAN_UP){
			Serial.println("Up");
		
			if(currentOrientation == PAC_MAN_LEFT)
				msgToSend = RIGHT;
			else if(currentOrientation == PAC_MAN_RIGHT)
				msgToSend = LEFT;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_RIGHT){
			Serial.println("Right");

			if(currentOrientation == PAC_MAN_UP)
				msgToSend = RIGHT;
			else if(currentOrientation == PAC_MAN_DOWN)
				msgToSend = LEFT;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_DOWN){
			Serial.println("Down");	

			if(currentOrientation == PAC_MAN_LEFT)
				msgToSend = LEFT;
			else if(currentOrientation == PAC_MAN_RIGHT)
				msgToSend = RIGHT;

			currentOrientation = msg;
		}
		else if(msg == PAC_MAN_LEFT){
			Serial.println("Left");	

			if(currentOrientation == PAC_MAN_UP)
				msgToSend = LEFT;
			else if(currentOrientation == PAC_MAN_DOWN)
				msgToSend = RIGHT;

			currentOrientation = msg;
		}
		

		communicationManager->SendMsg(LEFT);
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
			analogWrite(red, 255);
			analogWrite(green, 0);
			analogWrite(blue, 0);
		}
		else if(msg == BLUE_LED){
			analogWrite(red, 0);
			analogWrite(green, 0);
			analogWrite(blue, 255);			
		}
		else if(msg == YELLOW_LED){
			analogWrite(red, 255);
			analogWrite(green, 255);
			analogWrite(blue, 0);			
		}
		else if(msg == CIAN_LED){
			analogWrite(red, 0);
			analogWrite(green, 255);
			analogWrite(blue, 255);			
		}
		else if(msg == MAGENTA_LED){
			analogWrite(red, 255);
			analogWrite(green, 0);
			analogWrite(blue, 255);			
		}
		else if(msg == WHITE_LED){
			analogWrite(red, 255);
			analogWrite(green, 255);
			analogWrite(blue, 255);			
		}
		else if(msg == GREEN_LED){
			analogWrite(red, 0);
			analogWrite(green, 255);
			analogWrite(blue, 0);
		}
		else if(msg == TURN_ENDED){
			serverManager->SendMsg(JAVA_MESSAGE::JAVA_TURN_ENDED);
		}
	}
}

void loop() {
	MsPacManEngineCommunication();

	ReadMsg();
}
