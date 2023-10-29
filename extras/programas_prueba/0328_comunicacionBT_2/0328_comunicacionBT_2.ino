#include <SoftwareSerial.h>   // Incluimos la librería SoftwareSerial  

SoftwareSerial BT(27, 26);     // Definimos los pines RX y TX del Arduino conectados al Bluetooth

void setup()
{
  pinMode(27, INPUT);        // RX
  pinMode(26, OUTPUT);       // TX
  BT.begin(9600);            // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);        // Inicializamos el puerto serie  19200
  Serial1.begin(9600);
}

void loop()
{
  
  byte n = BT.available();
//  delay(800);
//  Serial.println(n);
  if(n != 0)// > 0)     // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.println("Recibiendo datos del Bluetooth...");
    String bluetooth = BT.readString();
    Serial.println(bluetooth);  // Imprimimos el dato recibido en el monitor serial
    Serial.write(BT.read());
    
  }
  
  if (Serial.available()) {  // Si llega un dato por el monitor serial se envía al puerto BT
     String message = Serial.readString();
//     BT.print(message);
     Serial.print("Enviando mensaje por Bluetooth: ");
     Serial.println(message);
     BT.write(Serial.read());
  }
}
