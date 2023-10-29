#include "MeSingleLineFollower.h"
#define BLACK 1
#define WHITE 0
#include <Arduino.h>
#define LINE 1
#define NOLINE 0


LineTracker::LineTracker(){
}

void LineTracker::Init(){
  pinMode(START_SENSOR_CENTER_LEFT, INPUT);
  pinMode(START_SENSOR_CENTER_RIGHT, INPUT);
  pinMode(START_SENSOR_EXT_LEFT, INPUT);
  pinMode(START_SENSOR_EXT_RIGHT, INPUT);

}


void LineTracker::Update(){
  
if(((linefollower_center_left.readSensor() == WHITE))  &&  ((linefollower_center_right.readSensor() == BLACK))){

  WHITEBLACK();

}else{
    
  if(((linefollower_center_left.readSensor() == BLACK))  &&  ((linefollower_center_right.readSensor() == WHITE))){

  BLACKWHITE();

  }else{
        
    if(((linefollower_center_left.readSensor() == WHITE))  &&  ((linefollower_center_right.readSensor() == WHITE))){
  
        WHITEWHITE1();

    }else{

        WHITEWHITE2();

      }

    }
  }
  
}

/**
 * @brief Devuelve si la linea de abajo del lado izquierdo del robot es negra o no
 * 
 * @return Color 
 */
//bool LineTracker::StartTurn(){
//
//  
//
//}

/**
 * @brief Devuelve si la linea de abajo del lado derecho robot es negra o no
 * 
 * @return Color 
 */
//bool LineTracker::EndTurn(){
//  
//
//
//}

/////////////////////////////////////////////////////////////////////////////////////////

void linefollower() {
  
if(((linefollower_center_left.readSensor() == NOLINE))  &&  ((linefollower_center_right.readSensor() == LINE))){

 motor_1.run(30 / 100.0 * 255);
 motor_9.run(30 / 100.0 * 255);
 motor_2.run(0 / 100.0 * 255);
 motor_10.run(0 / 100.0 * 255);
 

}else{
    
  if(((linefollower_center_left.readSensor() == LINE))  &&  ((linefollower_center_right.readSensor() == NOLINE))){

    motor_1.run(0 / 100.0 * 255);
    motor_9.run(0 / 100.0 * 255);
    motor_2.run(-30 / 100.0 * 255);
    motor_10.run(-30 / 100.0 * 255);

  }else{
        
    if(((linefollower_center_left.readSensor() == NOLINE))  &&  ((linefollower_center_right.readSensor() == NOLINE))){
  
      motor_1.run(25 / 100.0 * 255);
      motor_9.run(25 / 100.0 * 255);
      motor_2.run(-25 / 100.0 * 255);
      motor_10.run(-25 / 100.0 * 255);

    }else{

      motor_1.run(-30 / 100.0 * 255);
      motor_9.run(-30 / 100.0 * 255);
      motor_2.run(-30 / 100.0 * 255);
      motor_10.run(-30 / 100.0 * 255);

      }

    }
  }
}





void linefollower2() {
  
backward(20);
_delay(0.01);

while(!(((linefollower_center_left.readSensor() == HIGH))  &&  ((linefollower_center_right.readSensor() == HIGH)))){

forward(20);

if((linefollower_center_left.readSensor() == HIGH)){ // si sensor del centro izquierda lee alto, que corrija a la derecha

turnright(35);

} else if((linefollower_center_right.readSensor() == HIGH)){ // si sensor del centro derecha lee alto, que corrija a la izquierda

turnleft(35);

} // fin de la correccion de la linea central

//if((linefollower_ext_right.readSensor() == HIGH)){ // si el sensor del extremo derecha lee negro, que haga: 
//
//forward(15);
//_delay(0.05);
//parar(0);
//_delay(0.025);
//
//if((linefollower_ext_left.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){
//
//int caso = random(1,5);
//
//if (caso == 1) { // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija derecha 
//  
//  forward(20);
//  _delay(0.5);
//  turn90right(30);
//
//} else if (caso == 2){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija izquierda 
//
//  forward(20);
//  _delay(0.5);
//  turn90left(30);
//
//} else if (caso == 3){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} else {  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija seguir el rumbo 
//
//  forward(20);
//  _delay(0.2);
//
//}
//
//
//} else if((linefollower_ext_left.readSensor() == HIGH)){
//
//int caso = random(1,4);
//
//if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 
//  
//  forward(20);
//  _delay(0.5);
//  turn90right(30);
//
//} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 
//
//  forward(20);
//  _delay(0.5);
//  turn90left(30);
//
//} else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} 
//
//} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){
//
//int caso = random(1,4);
//
//if (caso == 1) { // si lee extremo derecha y los dos del centro, todo en negro, que elija derecha 
//  
//  forward(20);
//  _delay(0.5);
//  turn90right(30);
//
//} else if (caso == 2){  // si lee extremo derecha y los dos del centro, todo en negro, que siga de frente 
//
//  forward(20);
//  _delay(0.2);
//
//} else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} 
//
//} else {  
//
//forward(20);
//_delay(0.5);
//turn90right(30);
//
//
//}
//
//} // fin del if de lectura del sensor del extremo derecha
//
//if((linefollower_ext_left.readSensor() == HIGH)){ // si el sensor del extremo izquierdo lee negro, que haga: 
//
//forward(15);
//_delay(0.05);
//parar(0);
//_delay(0.025);
//
//if((linefollower_ext_right.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){
//
//int caso = random(1,5);
//
//if (caso == 1) { // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija derecha 
//  
//  forward(20);
//  _delay(0.5);
//  turn90right(30);
//
//} else if (caso == 2){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija izquierda 
//
//  forward(20);
//  _delay(0.5);
//  turn90left(30);
//
//} else if (caso == 3){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} else {  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija seguir el rumbo 
//
//  forward(20);
//  _delay(0.2);
//
//}
//
//
//} else if((linefollower_ext_right.readSensor() == HIGH)){
//
//int caso = random(1,4);
//
//if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 
//  
//  forward(20);
//  _delay(0.5);
//  turn90right(30);
//
//} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 
//
//  forward(20);
//  _delay(0.5);
//  turn90left(30);
//
//} else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} 
//
//} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){
//
//int caso = random(1,4);
//
//if (caso == 1) { // si lee extremo izquierda y los dos del centro, todo en negro, que elija izquierda 
//  
//  forward(20);
//  _delay(0.5);
//  turn90left(30);
//
//} else if (caso == 2){  // si lee extremo izquierda y los dos del centro, todo en negro, que siga de frente 
//
//  forward(20);
//  _delay(0.2);
//
//} else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 
//
//  forward(15);
//  _delay(0.5);
//  turnaround(30);
//
//} 
//
//} else {  
//
//forward(20);
//_delay(0.5);
//turn90left(30);
//
//}
//
//} // fin del if de lectura del sensor del extremo izquierda


} // del while de corrección 
}
