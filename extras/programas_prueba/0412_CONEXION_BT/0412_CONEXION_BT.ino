// esto funciona perfecto (para un lado) del MegaPi y hc05 
void setup()
{
  Serial.begin(9600);        // Inicializamos el puerto serie 
  Serial3.begin(115200);
//  Serial3.begin(9600);

}

void loop()
{
  byte n = Serial3.available();
//  Serial.println(n);
//  delay(10);
  if(n != 0)// > 0) // Si llega un dato por el puerto BT en Serial3 se envía al monitor serial
  {
    String bluetooth = Serial3.readString();
    Serial.print("Datos recibidos del Bluetooth: " + bluetooth);
  }
  
  if (Serial.available()) // Si llega un dato por el monitor serial se envía al puerto BT por Serial3
  {  
     String message = Serial.readString();
     Serial3.print("Datos enviados por el bluetooth: " + message);
     Serial.print("Datos enviados por el bluetooth: " + message);
  }
}
