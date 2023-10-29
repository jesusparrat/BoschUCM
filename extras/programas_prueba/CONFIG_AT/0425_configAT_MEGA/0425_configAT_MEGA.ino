#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
//SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
 
void setup()
{
  Serial.begin(9600);   // Inicializamos  el puerto serie  
//  BT.begin(38400);     // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial3.begin(38400);  // Inicializamos el puerto serie 3 BT en MegaPi (Para Modo AT 2)
}
 
void loop()
{
  if(Serial3.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(Serial3.read());    
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     Serial3.write(Serial.read());
  }
}
