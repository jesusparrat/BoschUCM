#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "MeSingleLineFollower.h"
#include "MeNewRGBLed.h"
#include <MeMegaPi.h>

MeMegaPiDCMotor motor_1(1); // motor delantero derecho
MeMegaPiDCMotor motor_9(9); // motor trasero derecho
MeMegaPiDCMotor motor_2(2); // motor delantero izquierdo
MeMegaPiDCMotor motor_10(10); // motor trasero izquierdo

MeSingleLineFollower barrier_front(60); // sensor IR central izquierdo
MeSingleLineFollower barrier_back(61); // sensor IR central derecho

MeSingleLineFollower linefollower_center_left(63); // sensor IR central izquierdo
MeSingleLineFollower linefollower_center_right(64); // sensor IR central derecho
MeSingleLineFollower linefollower_ext_left(66); // sensor IR extremo izquierdo
MeSingleLineFollower linefollower_ext_right(67); // sensor IR extremo derecho
MeNewRGBLed rgbled_left(68,4); // módulo RGB-LED izquierda
MeNewRGBLed rgbled_right(69,4); // módulo RGB-LED derecha
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;


void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime);
}


void setup() {

  Serial.begin(9600);
  Serial.println("intentando setup");

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

}


void loop() {
  
  linetracker();
  
  rightSensorCases();
  
  leftSensorCases();




}
