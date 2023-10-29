#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11);


int LEDROJO = A2;
int LEDVERDE = A1;
int LEDAZUL = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(38400);
  
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

char dato;

void loop(){
  if(miBT.available()){
    dato = miBT.read();
    Serial.println(dato);
    if(dato == '0'){
      analogWrite(LEDROJO, 0);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 255);        
    }
    else if(dato == '1'){
      analogWrite(LEDROJO, 0);
      analogWrite(LEDVERDE, 255);
      analogWrite(LEDAZUL, 0);       
    }
    else if(dato == '2'){
      analogWrite(LEDROJO, 255);
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 0);         
    }
  }
}
