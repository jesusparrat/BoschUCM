#include <EasyTransfer.h>

//#include <SoftEasyTransfer.h>

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0, 1);

//create object
EasyTransfer ET; 

struct DATA{
  int8_t num;
};

DATA myData;

int LEDROJO = A2;
int LEDVERDE = A1;
int LEDAZUL = A0;

void setup() {
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ET.begin(details(myData), &Serial);

  
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  analogWrite(LEDROJO, 0);
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDAZUL, 0);
}

void loop() {
  myData.num = 1;
  analogWrite(LEDROJO, 0);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDAZUL, 255);   
  ET.sendData();
  delay(1000);
  myData.num = 2;
  analogWrite(LEDROJO, 255);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDAZUL, 0); 
  ET.sendData();
  delay(1000);
}
