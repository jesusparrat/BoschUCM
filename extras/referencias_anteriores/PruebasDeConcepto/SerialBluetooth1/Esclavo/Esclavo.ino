#include <SoftwareSerial.h>

SoftwareSerial miBT(0,1);
int8_t DATO;
int LEDROJO = A2;
int LEDVERDE = A1;
int LEDAZUL = A0;

void setup(){

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  analogWrite(LEDROJO, 0);
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDAZUL, 0);
  
  
  miBT.begin(9600);
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());
  
}
int a = 0;
void loop(){
  if(miBT.available()){
    DATO = miBT.read();
    if(a%3 == 0)
    {
      analogWrite(LEDROJO, 255);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 0);
    }
    else if (a%3 == 1){
      analogWrite(LEDROJO, 0);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 255);      
    }
    else{
      analogWrite(LEDROJO, 255);
      analogWrite(LEDVERDE, 255);
      analogWrite(LEDAZUL, 255);   
      
    }
    a++;
  }
}


void led(){

}
