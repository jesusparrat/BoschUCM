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

MeSingleLineFollower barrier_front(60); // A6 sensor IR delantero
MeSingleLineFollower barrier_back(61); // A7 sensor IR trasero

MeSingleLineFollower linefollower_center_left(63); // A9 sensor IR central izquierdo
MeSingleLineFollower linefollower_center_right(64); // A10 sensor IR central derecho
MeSingleLineFollower linefollower_ext_left(65); // A11 sensor IR extremo izquierdo
MeSingleLineFollower linefollower_ext_right(66); // A12 sensor IR extremo derecho


double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;


void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime);
}

void PACMAN() {
  
  linetracker();
  leftSensorCases();
  rightSensorCases();
  comunicacion();

}


void setup() {

  Serial.begin(9600);
  Serial3.begin(9600);

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

}

bool MsPacMan = false;

void loop() {

    PACMAN();   

}
