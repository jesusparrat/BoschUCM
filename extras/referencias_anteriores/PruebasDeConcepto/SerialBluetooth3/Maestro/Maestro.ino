#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11);

void setup() {
  Serial.begin(9600);
  Serial.println("Listo maestro");
  miBT.begin(38400);
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());  
}

void loop(){
  miBT.print(0);
  delay(200);
  miBT.print(1);
  delay(200);
  miBT.print(2);
  delay(200);
}
