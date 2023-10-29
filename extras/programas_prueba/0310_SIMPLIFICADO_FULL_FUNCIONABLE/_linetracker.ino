void linetracker() {
  
if(((linefollower_center_left.readSensor() == 0))  &&  ((linefollower_center_right.readSensor() == 1))){

 motor_1.run(50 / 100.0 * 255);
 motor_9.run(50 / 100.0 * 255);
 motor_2.run(0 / 100.0 * 255);
 motor_10.run(0 / 100.0 * 255);

}else{
    
  if(((linefollower_center_left.readSensor() == 1))  &&  ((linefollower_center_right.readSensor() == 0))){

    motor_1.run(0 / 100.0 * 255);
    motor_9.run(0 / 100.0 * 255);
    motor_2.run(-50 / 100.0 * 255);
    motor_10.run(-50 / 100.0 * 255);

  }else{
        
    if(((linefollower_center_left.readSensor() == 0))  &&  ((linefollower_center_right.readSensor() == 0))){
  
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

  }

//if((linefollower_center_left.readSensor() == HIGH)){ // si sensor del centro izquierda lee alto, que corrija a la derecha
//
//turnright(35);
//
//} else if((linefollower_center_right.readSensor() == HIGH)){ // si sensor del centro derecha lee alto, que corrija a la izquierda
//
//turnleft(35);
//
//} // fin de la correccion de la linea central


}
