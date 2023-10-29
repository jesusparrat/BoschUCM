#include <EasyTransfer.h>

//#include <SoftEasyTransfer.h>
//#include <SoftwareSerial.h>


//SoftwareSerial mySerial(0, 1);

//SoftEasyTransfer ET; 

EasyTransfer ET;

struct DATA{
  int8_t num;
};

DATA myData;

void setup() {
  Serial.begin(9600);
  Serial.println("Listo");
  ET.begin(details(myData), &Serial);

  Serial.println("Listo Listo");
}

void loop() {
  if(ET.receiveData()){
    Serial.println("Dato recibido");
  }  
}
