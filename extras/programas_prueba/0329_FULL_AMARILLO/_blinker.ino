const int AZUL[] = {34, 32, 211};
const int AMBAR[] = {128, 55, 0};
const int ROJO[] = {128, 0, 0};
const int VERDE[] = {22, 124, 0};
const int NEGRO[] = {0, 0, 0};

void rgbled_both(int numLeds, const int* color) {
  rgbled_right.setColor(numLeds, color[0], color[1], color[2]);
  rgbled_right.show();
  rgbled_left.setColor(numLeds, color[0], color[1], color[2]);
  rgbled_left.show(); 
}


void rightBlinker() {
  for(int i = 0; i < 3; i++) {
    rgbled_right.setColor(0, 128, 55, 0);
    rgbled_right.show();
    _delay(0.25);
    rgbled_right.setColor(0, 0, 0, 0);
    rgbled_right.show();
    _delay(0.15);
  }
}

void leftBlinker() {
  for(int i = 0; i < 3; i++) {
    rgbled_left.setColor(0, 128, 55, 0);
    rgbled_left.show();
    _delay(0.25);
    rgbled_left.setColor(0, 0, 0, 0);
    rgbled_left.show();
    _delay(0.15);
  }
}



void forwardBlinker() { // verde ambos
  for (int i = 1; i < 5; i++) {
    rgbled_both(i, VERDE);
    _delay(0.15);
  }
  rgbled_both(0, NEGRO);
  _delay(0.001);
}

void backwardBlinker() { // rojo ambos
    rgbled_both(0, ROJO);
    _delay(0.2);
  for (int i = 5; i >= 1; i--) {
    rgbled_both(i, NEGRO);
    _delay(0.15);
  }
  rgbled_both(0, NEGRO);
  _delay(0.001);

}

void caughtBlinker() { // AMBOS AZUL
  for(int count = 0; count < 3; count++){
    rgbled_both(0, AZUL);
    _delay(0.25);
    for (int i = 5; i >= 1; i--) {
      rgbled_both(i, NEGRO);
      _delay(0.25);
    }
    rgbled_both(0, NEGRO);  
    _delay(0.001);
  }
}
