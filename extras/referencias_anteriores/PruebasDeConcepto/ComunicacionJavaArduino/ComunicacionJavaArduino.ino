#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(5,6); //pines de recibir, mandar
SoftEasyTransfer ET; 

enum ENTITY_STATE{
	SYNC_ATTEMP,
	SYNC
};

struct RECIEVE_DATA_STRUCTURE{
	int8_t id; //robot id
	ENTITY_STATE ent_state;
};

RECIEVE_DATA_STRUCTURE myData;


void setup() {
	Serial.begin(9600);
	while(!Serial);

	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
	myData.id = 0;


	while(true){
    Serial.println("Intentenado sincronizar");
		if(ET.receiveData() && myData.ent_state == SYNC_ATTEMP){
			
			Serial.println("Modulos conectados");
			myData.ent_state = SYNC;
			ET.sendData();
			break;
		}
	}
}

void loop() {


	// if(Serial.available() > 0){
	// 	byte incomingByte = Serial.read();

	// 	if(incomingByte != -1){
	// 		analogWrite(rojo, 0);
	// 		analogWrite(verde, 255);
	// 		analogWrite(azul, 0);  
			
			// myData.number = 2;
			// ET.sendData();
	// 	}
	// }
}
