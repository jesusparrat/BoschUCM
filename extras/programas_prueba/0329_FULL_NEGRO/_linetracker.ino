#pragma once

#include <Arduino.h>

#define LINE 1
#define NOLINE 0

void linetracker() {
  
if(((linefollower_center_left.readSensor() == NOLINE))  &&  ((linefollower_center_right.readSensor() == LINE))){

 motor_1.run(50 / 100.0 * 255);
 motor_9.run(50 / 100.0 * 255);
 motor_2.run(0 / 100.0 * 255);
 motor_10.run(0 / 100.0 * 255);
 

}else{
    
  if(((linefollower_center_left.readSensor() == LINE))  &&  ((linefollower_center_right.readSensor() == NOLINE))){

    motor_1.run(0 / 100.0 * 255);
    motor_9.run(0 / 100.0 * 255);
    motor_2.run(-50 / 100.0 * 255);
    motor_10.run(-50 / 100.0 * 255);

  }else{
        
    if(((linefollower_center_left.readSensor() == NOLINE))  &&  ((linefollower_center_right.readSensor() == NOLINE))){
  
      motor_1.run(30 / 100.0 * 255);
      motor_9.run(30 / 100.0 * 255);
      motor_2.run(-30 / 100.0 * 255);
      motor_10.run(-30 / 100.0 * 255);

    }else{

      motor_1.run(-50 / 100.0 * 255);
      motor_9.run(-50 / 100.0 * 255);
      motor_2.run(-50 / 100.0 * 255);
      motor_10.run(-50 / 100.0 * 255);

      }

    }
  if ((barrier_front.readSensor() == LOW)){
    _delay(0.2);
      if ((barrier_front.readSensor() == LOW)){

          turnaround(30);
      }
    }
  if ((barrier_back.readSensor() == LOW)){
    _delay(0.2);
      if ((barrier_back.readSensor() == LOW)){

          turnaround(30);
      }
    }
  }


}
