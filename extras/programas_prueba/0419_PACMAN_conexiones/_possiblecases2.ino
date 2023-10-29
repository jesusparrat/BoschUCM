// posibles casos con switches

 void leftSensorCasesSwitch() { // casos posibles para el sensor del extremo izquierda
  switch(linefollower_ext_left.readSensor()) {
    
    case HIGH: // si el sensor del extremo izquierdo lee negro
          
      parar(0);      
      int caso = Serial3.read();
       
      switch(caso) {
        
//          case 1: // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija derecha 
//            rightBlinker();
//            turn90right(25);
//            break;
          
          case 1: // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija izquierda 
            forwardBlinker();
            forward(30);
            _delay(0.05);
            break;
         
          default: // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija seguir el rumbo 
            leftBlinker();
            turn90left(25);
            break;
        }
        
      }
  }

 
      /* else if((linefollower_ext_right.readSensor() == HIGH)){
        
        int caso = random(1,3);
        
        switch(caso) {
        
          case 1: // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 
            rightBlinker();
            turn90right(25);
            break;
          
          default: // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 
            leftBlinker();
            turn90left(25);
            break;
        }
      } else if((linefollower_center_left.readSensor() == LOW) || (linefollower_center_right.readSensor() == LOW)){
        
        int caso = random(1,4);
        
        switch(caso) {
        
          case 1: // si lee extremo izquierda y los dos del centro, todo en negro, que elija izquierda 
            leftBlinker();
            turn90left(25);
            break;
          
          default: // si lee extremo izquierda y los dos del centro, todo en negro, que siga de frente 
            forwardBlinker();
            forward(30);
            _delay(0.05);
            break;
        }
      } else {  
        leftBlinker();
        turn90left(25);
        break;
      }
      break;
    default:
      break;
  }
}*/
