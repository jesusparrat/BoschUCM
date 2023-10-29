float number = 0;
float number2 = 4;


void rightBlinker() { // ambar derecha
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

void leftBlinker() { // ambar izquierda
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

void forwardBlinker() { // verde ambos
  for (int i = 1; i < 5; i++) {
    rgbled_right.setColor(i, 22, 124, 0);
    rgbled_right.show();
    rgbled_left.setColor(i, 22, 124, 0);
    rgbled_left.show();  
    _delay(0.1);
  }
  rgbled_right.setColor(0,0,0,0);
  rgbled_right.show();
  rgbled_left.setColor(0,0,0,0);
  rgbled_left.show();   
  _delay(0.001);
}

void backwardBlinker() { // rojo ambos
    rgbled_right.setColor(0, 124, 0, 0);
    rgbled_right.show();
    rgbled_left.setColor(0, 124, 0, 0);
    rgbled_left.show();  
    _delay(0.1);
  for (int i = 5; i >= 1; i--) {
    rgbled_right.setColor(i, 0, 0, 0);
    rgbled_right.show();
    rgbled_left.setColor(i, 0, 0, 0);
    rgbled_left.show();  
    _delay(0.25);
  }
  rgbled_right.setColor(0,0,0,0);
  rgbled_right.show();
  rgbled_left.setColor(0,0,0,0);
  rgbled_left.show();   
  _delay(0.001);

}

void caughtBlinker() { // azul ambos
  for(int count=0;count<3;count++){
    rgbled_right.setColor(0, 34, 32, 211);
    rgbled_right.show();
    rgbled_left.setColor(0, 34, 32, 211);
    rgbled_left.show();  
    _delay(0.25);
  for (int i = 5; i >= 1; i--) {
    rgbled_right.setColor(i, 0, 0, 0);
    rgbled_right.show();
    rgbled_left.setColor(i, 0, 0, 0);
    rgbled_left.show();  
    _delay(0.075);
  }
  rgbled_right.setColor(0,0,0,0);
  rgbled_right.show();
  rgbled_left.setColor(0,0,0,0);
  rgbled_left.show();   
  _delay(0.001);
}
}
