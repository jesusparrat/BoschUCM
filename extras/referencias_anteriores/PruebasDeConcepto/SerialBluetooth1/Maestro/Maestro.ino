#include <SoftwareSerial.h>

SoftwareSerial miBT(0,1);

void setup() {
  miBT.begin(9600);
}

int8_t dato;

void loop(){
  dato = 1;
  miBT.print(dato);
  delay(1000);
  miBT.print(dato);
  delay(1000);
}
