#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11);
char DATO = 0;
int LEDROJO = A2;
int LEDVERDE = A1;
int LEDAZUL = A0;

void setup(){
  Serial.begin(9600);
  Serial.println("listo");

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  analogWrite(LEDROJO, 0);
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDAZUL, 0);
  
  
  miBT.begin(38400);
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());
  
}

void loop(){
  configuracion();
}


void led(){
    if(miBT.available()){
    DATO = miBT.read();
    if(DATO == '1')
    {
      analogWrite(LEDROJO, 255);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 0);
    }
    else if (DATO == '2'){
      analogWrite(LEDROJO, 0);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 255);      
    }
  }
}
