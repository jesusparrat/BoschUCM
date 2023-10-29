#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(5,6);


SoftEasyTransfer ET_in; 
SoftEasyTransfer ET_out; 


struct RECIEVE_DATA_STRUCTURE{
  int8_t id;
  int8_t number;
};

enum RESPONSE{
  OK,
  ERR
};

RESPONSE myDataIn;
RECIEVE_DATA_STRUCTURE myDataOut;



void setup() {
  Serial.begin(9600);
  Serial.println("Inicializamos");
  miBT.begin(9600);
  
  ET_in.begin(details(myDataIn), &miBT);
  ET_out.begin(details(myDataOut), &miBT);

  myDataOut.id = 0;

  while(true){
    miBT.flush();
    ET_out.sendData();
    miBT.flush();

    if(ET_in.receiveData()){
      Serial.println("Sincronizados");
      break;
    }
    
    delay(10);
  }
}


void loop(){

  

  /*if(miBT.available()){
    Serial.println(miBT.read());
  }
  miBT.flush();
  miBT.print('a');
  miBT.flush();*/
}
