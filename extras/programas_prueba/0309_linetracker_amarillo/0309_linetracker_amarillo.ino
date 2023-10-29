// funciona de forma aleatoria para TODOS los cruces
// código abreviado

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "src/MeSingleLineFollower.h"
#include "src/MeCollisionSensor.h"
#include "src/MeBarrierSensor.h"
#include "src/MeNewRGBLed.h"
#include <MeMegaPi.h>

MeMegaPiDCMotor motor_1(1);
MeMegaPiDCMotor motor_9(9);
MeMegaPiDCMotor motor_2(2);
MeMegaPiDCMotor motor_10(10);
MeBarrierSensor barrier_60(60);
MeBarrierSensor barrier_61(61);
MeSingleLineFollower linefollower_center_left(63);
MeSingleLineFollower linefollower_center_right(64);
MeSingleLineFollower linefollower_center(65);
MeSingleLineFollower linefollower_ext_left(66);
MeSingleLineFollower linefollower_ext_right(67);
MeNewRGBLed rgbled_left(68,4); // LED izquierda
MeNewRGBLed rgbled_right(69,4); // LED derecha
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;


float x = 0;

void motor_foward_left_run(int16_t speed)
{
   motor_10.run(-speed);
}

void motor_foward_right_run(int16_t speed)
{
  motor_1.run(speed);
}

void motor_back_left_run(int16_t speed)
{
  motor_2.run(-speed);
}

void motor_back_right_run(int16_t speed)
{
  motor_9.run(speed);
}

void move_control(int16_t vx, int16_t vy, int16_t vw)
{
  int16_t foward_left_speed;
  int16_t foward_right_speed;
  int16_t back_left_speed;
  int16_t back_right_speed;

  foward_left_speed = vy + vx + vw;
  foward_right_speed = vy - vx - vw;
  back_left_speed = vy - vx + vw;
  back_right_speed = vy + vx - vw;

  motor_foward_left_run(foward_left_speed);
  motor_foward_right_run(foward_right_speed);
  motor_back_left_run(back_left_speed);
  motor_back_right_run(back_right_speed);
}

void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

}

void _loop() {
}

int velocidad = 90;

void forward(int16_t speed){
  move_control(0, speed / 100.0 * 255, 0);
}

void backward(int16_t speed){
  move_control(0, -speed / 100.0 * 255, 0); 
}

void turnright(int16_t speed){
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);
}

void turnleft(int16_t speed){
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);
}

void turn90right(int16_t speed){ // giro 90 a derechas
  forward(20);
  _delay(0.4);  
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);            
  _delay(0.8);
}

void turn90left(int16_t speed){  // giro 90 a izquierdas
  forward(20);
  _delay(0.4);  
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);            
  _delay(0.8);
}

void parar(int16_t speed){
  motor_1.run(0);
  motor_9.run(0);
  motor_2.run(0);
  motor_10.run(0);
}

void turnaround(int16_t speed) {  // para vuelta 180 grados velocidad a 30
  forward(25);
  _delay(0.5);  
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);
  _delay(1.75);
}


void rightBlinker() { // ambar
  rgbled_right.setColor(0, 128, 55, 0);
  rgbled_right.show();
  _delay(0.3); 
  rgbled_right.setColor(0, 0, 0, 0);
  rgbled_right.show();
  _delay(0.2);
  rgbled_right.setColor(0, 128, 55, 0);
  rgbled_right.show();
  _delay(0.3);
  rgbled_right.setColor(0, 0, 0, 0);
  rgbled_right.show();
  _delay(0.05);

}

void leftBlinker() { // ambar
  rgbled_left.setColor(0, 128, 55, 0);
  rgbled_left.show();
  _delay(0.3); 
  rgbled_left.setColor(0, 0, 0, 0);
  rgbled_left.show();
  _delay(0.2);
  rgbled_left.setColor(0, 128, 55, 0);
  rgbled_left.show();
  _delay(0.3);
  rgbled_left.setColor(0, 0, 0, 0);
  rgbled_left.show();
  _delay(0.05);

}

void forwardBlinker() { // verde
  rgbled_left.setColor(0, 22, 124, 0);
  rgbled_left.show();
  rgbled_right.setColor(0, 22, 124, 0);
  rgbled_right.show();  
  _delay(0.3);
  rgbled_left.setColor(0, 0, 0, 0);
  rgbled_left.show();
  _delay(0.001);
  rgbled_right.setColor(0, 0, 0, 0);
  rgbled_right.show();
  _delay(0.001);  

}

void backwardBlinker() { // rojo
  rgbled_left.setColor(0, 124, 0, 0);
  rgbled_left.show();
  rgbled_right.setColor(0, 124, 0, 0);
  rgbled_right.show();
  _delay(0.3);
  rgbled_left.setColor(0, 0, 0, 0);
  rgbled_left.show();
  _delay(0.001);
  rgbled_right.setColor(0, 0, 0, 0);
  rgbled_right.show();
  _delay(0.001);  

}

void pilladoBlinker() { // rojo
for (int i = 0; i < 5; i++) {
    rgbled_left.setColor(0, 34, 32, 211);
    rgbled_left.show();
    rgbled_right.setColor(0, 34, 32, 211);
    rgbled_right.show();
    _delay(0.05);
}
  rgbled_left.setColor(0, 0, 0, 0);
  rgbled_left.show();
  _delay(0.001);
  rgbled_right.setColor(0, 0, 0, 0);
  rgbled_right.show();
  _delay(0.001);  
}

void readAllSensors() {
  forward(15);
  _delay(0.05);
  parar(0);
  _delay(0.025);
}


void loop() {

backward(20);
_delay(0.01);

while(!(((linefollower_center_left.readSensor() == HIGH))  &&  ((linefollower_center_right.readSensor() == HIGH)))){

_loop();

forward(25);

if((linefollower_center_left.readSensor() == HIGH)){ // si sensor del centro izquierda lee alto, que corrija a la derecha

turnright(35);

} else if((linefollower_center_right.readSensor() == HIGH)){ // si sensor del centro derecha lee alto, que corrija a la izquierda

turnleft(35);

} // fin de la correccion de la linea central

if((linefollower_ext_right.readSensor() == HIGH)){ // si el sensor del extremo derecha lee negro, que haga: 

readAllSensors();

if((linefollower_ext_left.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,5);

if (caso == 1) { // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(30);

} else if (caso == 2){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(30);

} else if (caso == 3){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} else {  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija seguir el rumbo 

  forwardBlinker();
  forward(25);
  _delay(0.2);

}


} else if((linefollower_ext_left.readSensor() == HIGH)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(30);

} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(30);

} else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} 

} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo derecha y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(30);

} else if (caso == 2){  // si lee extremo derecha y los dos del centro, todo en negro, que siga de frente 

  forwardBlinker();
  forward(25);
  _delay(0.2);

} else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} 

} else {  

rightBlinker();
turn90right(30);


}

} // fin del if de lectura del sensor del extremo derecha

if((linefollower_ext_left.readSensor() == HIGH)){ // si el sensor del extremo izquierdo lee negro, que haga: 

readAllSensors();

if((linefollower_ext_right.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,5);

if (caso == 1) { // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(30);

} else if (caso == 2){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(30);

} else if (caso == 3){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} else {  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija seguir el rumbo 

  forwardBlinker();
  forward(25);
  _delay(0.2);

}


} else if((linefollower_ext_right.readSensor() == HIGH)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(30);

} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(30);

} else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} 

} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo izquierda y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(30);

} else if (caso == 2){  // si lee extremo izquierda y los dos del centro, todo en negro, que siga de frente 

  forwardBlinker();
  forward(25);
  _delay(0.2);

} else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} 

} else {  

leftBlinker();
turn90left(30);

}

} // fin del if de lectura del sensor del extremo izquierda


} // del while de corrección 





_loop();

}
