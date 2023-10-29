#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11);
SoftEasyTransfer ET; 

struct RECIEVE_DATA_STRUCTURE{
  int8_t id;
  int8_t number;
};

RECIEVE_DATA_STRUCTURE myData;

void setup() {
  miBT.begin(38400);
  ET.begin(details(myData), &miBT);
  myData.id = 0;
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());  
}

void loop(){
  myData.number = 10;
  ET.sendData();
  delay(200);
  myData.number = 20;
  ET.sendData();
  delay(200);
  myData.number = 30;
  ET.sendData();
  delay(200);
}
