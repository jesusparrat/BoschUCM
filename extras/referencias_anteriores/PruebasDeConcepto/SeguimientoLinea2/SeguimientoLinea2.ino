#define LINEA 1
#define PASILLO 0

#define VELOCIDAD_NORMAL 200
#define VELOCIDAD_REDUCIDA 60

#define TIEMPO_ROTACION 350

int velocidadDerecha = 11; //derecha
int delanteDerecha = A0;
int atrasDerecha = A1;
int delanteIzquierda = A2;
int atrasIzquierda = A3;
int velocidadIzquierda = 10; //izquierda

int SENSOR_I = 7;
int SENSOR_C = 6;
int SENSOR_D = 5;


void setup() {
  pinMode(velocidadDerecha, OUTPUT);
  pinMode(delanteDerecha, OUTPUT);
  pinMode(atrasDerecha, OUTPUT);
  pinMode(delanteIzquierda, OUTPUT);
  pinMode(atrasIzquierda, OUTPUT);
  pinMode(velocidadIzquierda, OUTPUT);

  digitalWrite(velocidadDerecha, 100);
  digitalWrite(velocidadIzquierda, 100);

  pinMode(SENSOR_I, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_D, INPUT);

  Serial.begin(9600);
}


void recta(bool marchaAlante){
  if(marchaAlante){
    digitalWrite(delanteIzquierda, LOW);
    digitalWrite(atrasIzquierda, HIGH);
    digitalWrite(delanteDerecha, HIGH);
    digitalWrite(atrasDerecha, LOW);
  }
  else {
    digitalWrite(delanteIzquierda, HIGH);
    digitalWrite(atrasIzquierda, LOW);
    digitalWrite(delanteDerecha, LOW);
    digitalWrite(atrasDerecha, HIGH);
  }
}

void noventagrados(bool derecha){
  if(derecha){
    analogWrite(velocidadIzquierda, VELOCIDAD_NORMAL);
    analogWrite(velocidadDerecha, VELOCIDAD_NORMAL);

    digitalWrite(delanteIzquierda, LOW);
    digitalWrite(atrasIzquierda, HIGH);
    digitalWrite(delanteDerecha, LOW);
    digitalWrite(atrasDerecha, HIGH);
  }
  else {
    analogWrite(velocidadIzquierda, VELOCIDAD_NORMAL);
    analogWrite(velocidadDerecha, VELOCIDAD_NORMAL);   

    digitalWrite(delanteIzquierda, HIGH);
    digitalWrite(atrasIzquierda, LOW);
    digitalWrite(delanteDerecha, HIGH);
    digitalWrite(atrasDerecha, LOW);
  }
  delay(TIEMPO_ROTACION);
}

void cientoochentagrados(){
  digitalWrite(delanteIzquierda, LOW);
  digitalWrite(atrasIzquierda, HIGH);
  digitalWrite(delanteDerecha, LOW);
  digitalWrite(atrasDerecha, HIGH);
  delay(460);
}

void parada(){
  digitalWrite(delanteDerecha, LOW);
  digitalWrite(atrasDerecha, LOW);
  digitalWrite(delanteIzquierda, LOW);
  digitalWrite(atrasIzquierda, LOW);
}



void seguimientoLinea(){
  int izquierda = digitalRead(SENSOR_I);
  int centro = digitalRead(SENSOR_C);
  int derecha = digitalRead(SENSOR_D);

  if(izquierda == LINEA && centro == PASILLO && derecha == LINEA){ //recto
    recta(true);
    analogWrite(velocidadIzquierda, VELOCIDAD_NORMAL);
    analogWrite(velocidadDerecha, VELOCIDAD_NORMAL);
  }
  // else if(izquierda == LINEA && centro == LINEA && derecha == LINEA){ //Giro 90 grados
  //   recta(false);
  //   delay(100);
  //   noventagrados(false);
  //   parada();
  //   delay(100);
  //   recta(true);
  //   delay(300);
  // }
  else if (izquierda == PASILLO && derecha == LINEA) { //desvio derecha
    recta(true);

    analogWrite(velocidadDerecha, VELOCIDAD_REDUCIDA);
  }
  else if(izquierda == LINEA && derecha == PASILLO){ //desvio izquierda
    recta(true);

    analogWrite(velocidadIzquierda, VELOCIDAD_REDUCIDA);
  }
  else{ //parada
    parada();
  }
}



void loop() {
  seguimientoLinea();
}
