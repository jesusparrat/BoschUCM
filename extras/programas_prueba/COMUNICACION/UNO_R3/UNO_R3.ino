#include <SoftwareSerial.h>  // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos  pines RX y TX del Arduino UNO R3 conectados HC-05

//pines para la led rgb
int red = 6;
int green = 5;
int blue = 3;

void rojo() {
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);
}

void azul() {
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 255);
}

void verde() {
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 0);
}

void nada() {
  analogWrite(red, 1);
  analogWrite(green, 1);
  analogWrite(blue, 1);
}
 
void setup()
{
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  BT.begin(9600);     // Inicializamos el puerto serie simulado del BT del HC-05 

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  rojo();
  
}
 

void loop() {

  if(BT.available() != 0)// > 0) // Si llega un dato por el puerto BT en Serial3 se envía al monitor serial
  {
    String bluetooth = BT.readString();
    Serial.print("Datos recibidos del Bluetooth: " + bluetooth + '\n');
    azul();
    delay(2000);
    nada();
  }

  
  if (Serial.available()) // Si llega un dato por el monitor serial se envía al puerto BT por Serial3
  {  
    String message = Serial.readString();
    BT.print(message);
    Serial.print("Datos enviados por el bluetooth: " + message);
    verde();
    delay(2000);
    nada();
  }
  
}
