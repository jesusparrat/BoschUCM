// funciona de forma aleatoria para un cruce de ambos lados
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
//  motor_foward_left_run(speed);
//  motor_foward_right_run(speed);
//  motor_back_left_run(speed);
//  motor_back_right_run(speed);
}

void backward(int16_t speed){
  move_control(0, -speed / 100.0 * 255, 0); 
//  motor_foward_left_run(-speed);
//  motor_foward_right_run(-speed);
//  motor_back_left_run(-speed);
//  motor_back_right_run(-speed);
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

void turn90right(int16_t speed){ // derecha
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);            
  _delay(0.9);
  }

void turn90left(int16_t speed){  // izquierda
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);            
  _delay(0.9);
  }

void parar(int16_t speed){
  motor_1.run(0);
  motor_9.run(0);
  motor_2.run(0);
  motor_10.run(0);
}

void turnaround(int16_t speed) {  // para vuelta 180 grados velocidad a 30
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);
  _delay(1.675);
  }






void loop() {

  backward(20);
  _delay(0.01);

  while(!(((linefollower_center_left.readSensor() == HIGH))  &&  ((linefollower_center_right.readSensor() == HIGH))))
  {
    _loop();

    forward(20);

    if((linefollower_center_left.readSensor() == HIGH)){ // si sensor del centro izquierda lee alto, que corrija a la derecha

      turnright(35);
    }
    else if((linefollower_center_right.readSensor() == HIGH)){ // si sensor del centro derecha lee alto, que corrija a la izquierda

      turnleft(35);

    } // fin de la correccion de la linea central

    if((linefollower_ext_right.readSensor() == HIGH)){ // si el sensor del extremo derecha lee negro, que haga: 

      forward(15);
      _delay(0.05);
      parar(0);
      _delay(5);

      if((linefollower_ext_left.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){

        int caso1 = rand() % 3;
        
        if (caso1 == 0) { // si lee derecha e izquierda que elija derecha 

            turnaround(30);        
          
        } else if (caso1 == 1){  // si lee derecha e izquierda que elija izquierda 
          
            forward(20);
            _delay(0.5);
            turn90left(30);
          
          } else if (caso1 == 2){  // si lee derecha e izquierda que elija izquierda 
          
            forward(20);
            _delay(0.5);
            turn90right(30);
          
          }

      }

      else if((linefollower_ext_left.readSensor() == HIGH)){

        int caso1 = rand(0, 3);
        
        if (caso1 == 0) { // si lee derecha e izquierda que elija derecha 

            turnaround(30);        
          
        } else if (caso1 == 1){  // si lee derecha e izquierda que elija izquierda 
          
//            forward(20);
//            _delay(0.5);
//            turn90left(30);
          
          } else if (caso1 == 2){  // si lee derecha e izquierda que elija izquierda 

          turnaround(100);
//            forward(20);
//            _delay(0.5);
//            turn90right(30);
          
          }
      }
      
      else if((linefollower_ext_right.readSensor() == HIGH)){ // no entiendo por qué le tengo que especificar de nuevo que si lee ext derecho gire 90 a derecha pero solo funciona así, si no pongo esto después del ultimo else if hace el último else 

      forward(20);
      _delay(0.5);
      turn90right(30);

      }
    }
    
  }


  
  _loop();
}



























//      if (linefollower_ext_left.readSensor() == HIGH && linefollower_ext_right.readSensor() == HIGH) {
//        
//        int direction = rand() % 3;
//        
//        if (direction == 0) { // si lee derecha e izquierda que elija derecha 
//        
//            forward(20);
//            _delay(0.5);
//            turn90right(30);
//          
//        } else if (direction == 1){  // si lee derecha e izquierda que elija izquierda 
//          
//            forward(20);
//            _delay(0.5);
//            turn90left(30);
//          
//          } else if (direction == 2){  // si lee derecha e izquierda que elija izquierda 
//          
//            turnaround(50);
//          
//          }
//        }    
//          else if(linefollower_66.readSensor() == HIGH){  //  si sólo lee el de la izquierda, que gire a izquierda
//
//            forward(20);
//            _delay(0.5);
//            turn90left(30);
//        
//    }
//          else if(linefollower_67.readSensor() == HIGH){  // lo mismo a derechas
//
//            forward(20);
//            _delay(0.5);
//            turn90right(30);
//        
//    }
