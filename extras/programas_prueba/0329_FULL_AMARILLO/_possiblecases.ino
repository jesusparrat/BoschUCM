// posibles casos sin marcha atras




void leftSensorCases() { // casos posibles para el sensor del extremo izquierda

if((linefollower_ext_left.readSensor() == HIGH)){ // si el sensor del extremo izquierdo lee negro, que haga: 

readAllSensors();

if((linefollower_ext_right.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(25);

} else if (caso == 2){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(25);

} /* else if (caso == 3){  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} */ else {  // si lee extremo izquierda, extremo derecha y los dos del centro, todo en negro, que elija seguir el rumbo 

  forwardBlinker();
  forward(30);
  _delay(0.05);

}


} else if((linefollower_ext_right.readSensor() == HIGH)){

int caso = random(1,3);

if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(25);

} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(25);

} /* else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} */

} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo izquierda y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(25);

} else if (caso == 2){  // si lee extremo izquierda y los dos del centro, todo en negro, que siga de frente 

  forwardBlinker();
  forward(30);
  _delay(0.05);

} /* else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} */

} else {  

leftBlinker();
turn90left(25);

}

} // fin del if de lectura del sensor del extremo izquierda

}

void rightSensorCases() {
  if((linefollower_ext_right.readSensor() == HIGH)){ // si el sensor del extremo derecha lee negro, que haga: 

readAllSensors();

if((linefollower_ext_left.readSensor() == HIGH)  &&  (linefollower_center_left.readSensor() == LOW)  &&  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,4);

if (caso == 1) { // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(25);

} else if (caso == 2){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(25);

} /* else if (caso == 3){  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

}*/ else {  // si lee extremo derecha, extremo izquierda y los dos del centro, todo en negro, que elija seguir el rumbo 

  forwardBlinker();
  forward(30);
  _delay(0.05);

}


} else if((linefollower_ext_left.readSensor() == HIGH)){

int caso = random(1,3);

if (caso == 1) { // si lee extremo derecha y extremo izquierda, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(25);

} else if (caso == 2){  // si lee extremo derecha y extremo izquierda, todo en negro, que elija izquierda 

  leftBlinker();
  turn90left(25);

} /* else {  // si lee extremo derecha y extremo izquierda, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} */

} else if((linefollower_center_left.readSensor() == LOW)  ||  (linefollower_center_right.readSensor() == LOW)){

int caso = random(1,3);

if (caso == 1) { // si lee extremo derecha y los dos del centro, todo en negro, que elija derecha 

  rightBlinker();
  turn90right(25);

} else if (caso == 2){  // si lee extremo derecha y los dos del centro, todo en negro, que siga de frente 

  forwardBlinker();
  forward(30);
  _delay(0.05);

} /* else {  // si lee extremo derecha y los dos del centro, todo en negro, que elija volver hacia atrás 

  backwardBlinker();
  turnaround(30);

} */

} else {  

rightBlinker();
turn90right(25);


}

} // fin del if de lectura del sensor del extremo derecha

}
