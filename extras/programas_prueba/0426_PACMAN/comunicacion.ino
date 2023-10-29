void comunicacion() {
if (Serial3.available() > 0) {  // Si hay datos en el puerto Serial3
    String message = Serial3.readString();  // Leer el mensaje recibido
    message.trim();  // Eliminar los espacios en blanco al inicio y final del mensaje
    Serial.println("Mensaje recibido: " + message);  // Imprimir el mensaje en el monitor serial
    
    // Determinar la acción a realizar según el mensaje recibido
    switch(message.charAt(0)) {
      case 'U':
        MsPacMan = false;      
        forward(17);  // Mover hacia delante con la velocidad actual
        break;
      case 'B':
        MsPacMan = false;      
        backward(17);  // Mover hacia atrás con la velocidad actual
        break;
      case 'S':
        MsPacMan = false;
        parar(0);  // Detener el movimiento del robot
        break;
      case 'P':
        MsPacMan = false;  // Cambiar el valor de shouldRunLinetracker a verdadero
        break;
      case 'H':
        caughtBlinker();  // Cambiar el valor de shouldRunLinetracker a verdadero
        Serial3.print("HOLA");   
        break;           
      case 'L':
        leftBlinker();  
        turn90left(30);
        Serial3.print("izquierda");   
        break;        
      case 'R':
        rightBlinker();  
        turn90right(30);
        Serial3.print("derecha");   
        break;                
      default:
        Serial3.println("Mensaje no válido");  // Si el mensaje no es reconocido, imprimir un mensaje de error
        break;
    }
  }


  if(Serial3.available() != 0) {
    String bluetooth = Serial3.readString();
    Serial.print("Datos recibidos del Bluetooth: " + bluetooth);
  }
  
  if (Serial.available()) {  
     String message = Serial.readString();
     Serial3.print("Datos enviados por el puerto serie en bluetooth: " + message);
     Serial.print("Datos enviados por el puerto serie en bluetooth: " + message);
  }
}


void comunicacion2() {
if (Serial3.available() > 0) {  // Si hay datos en el puerto Serial3
    String messageBTtoS = Serial3.readString();  // Leer el mensaje recibido
    messageBTtoS.trim();  // Eliminar los espacios en blanco al inicio y final del mensaje
    Serial.println("Mensaje recibido: " + messageBTtoS);  // Imprimir el mensaje en el monitor serial
    
    // Determinar la acción a realizar según el mensaje recibido
    switch(messageBTtoS.charAt(0)) {
      case 'U':
        forward(17);  // Mover hacia delante con la velocidad actual
        break;
      case 'B':
        backward(17);  // Mover hacia atrás con la velocidad actual
        break;
      case 'S':
        parar(0);  // Detener el movimiento del robot
        break;
      case 'P':
        MsPacMan = true;  // Cambiar el valor de shouldRunLinetracker a verdadero
        break;
      case 'H':
        caughtBlinker();  // Cambiar el valor de shouldRunLinetracker a verdadero
        Serial3.print("HOLA");   
        break;           
      case 'L':
        leftBlinker();  
        turn90left(30);
        Serial3.print("izquierda");   
        break;        
      case 'R':
        rightBlinker();  
        turn90right(30);
        Serial3.print("derecha");   
        break;                
      default:
        Serial3.println("Mensaje no válido");  // Si el mensaje no es reconocido, imprimir un mensaje de error
        break;
    }
}

//    if(Serial3.available() != 0) {
//      String bluetooth = Serial3.readString();
//      Serial.print("Datos recibidos del Bluetooth: " + bluetooth);
//    }
//    
//    if (Serial.available()) {  
//       String messageStoBT = Serial.readString();
//       Serial3.print("Datos enviados por bluetooth: " + messageStoBT);
//       Serial.print("Datos enviados por bluetooth: " + messageStoBT);
//    }
  
}
