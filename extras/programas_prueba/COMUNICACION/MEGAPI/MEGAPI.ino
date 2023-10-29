void setup()
{
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  Serial3.begin(9600);     // Inicializamos el puerto serie simulado del BT del HC-05 
}
 

void loop() {

  if(Serial3.available() != 0)// > 0) // Si llega un dato por el puerto BT en Serial3 se envía al monitor serial
  {
    String bluetooth = Serial3.readString();
    Serial.print("Datos recibidos del Bluetooth: " + bluetooth + '\n');
  }
  
  if (Serial.available()) // Si llega un dato por el monitor serial se envía al puerto BT por Serial3
  {  
     String message = Serial.readString();
     Serial3.print(message);
     Serial.print("Datos enviados por el bluetooth: " + message);
  }
  
}
