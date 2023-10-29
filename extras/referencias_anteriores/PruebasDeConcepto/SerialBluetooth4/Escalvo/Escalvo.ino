#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11);


int LEDROJO = A2;
int LEDVERDE = A1;
int LEDAZUL = A0;

SoftEasyTransfer ET;

struct RECIEVE_DATA_STRUCTURE{
  int8_t id;
  int8_t number;
};


RECIEVE_DATA_STRUCTURE myData;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(38400);
  ET.begin(details(myData), &miBT);
  
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  analogWrite(LEDROJO, 255);
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDAZUL, 255);
  
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());  
}

void loop(){
  if(ET.receiveData()){
    Serial.print("ID: ");
    Serial.print(myData.id);
    Serial.print(", Data read: ");
    Serial.println(myData.number);
  }
}
