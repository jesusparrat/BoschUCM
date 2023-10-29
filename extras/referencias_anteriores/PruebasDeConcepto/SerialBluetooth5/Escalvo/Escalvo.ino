#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(3,9);



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

RECIEVE_DATA_STRUCTURE myDataIn;
RESPONSE myDataOut;


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(9600);
  ET_in.begin(details(myDataIn), &miBT);
  ET_out.begin(details(myDataOut), &miBT);


  while(true){
    if(ET_in.receiveData()){
      Serial.println("Sincronizados");
        
      miBT.flush();
      myDataOut = OK;
      ET_out.sendData();
      miBT.flush();
      break;
    }      
    delay(10);
  }
}


void loop(){
  
  //delay(10);
  
  
  /*if(miBT.available()){
    Serial.println(miBT.read());
    miBT.flush();
    miBT.print('b');
    miBT.flush();
  }*/
}
