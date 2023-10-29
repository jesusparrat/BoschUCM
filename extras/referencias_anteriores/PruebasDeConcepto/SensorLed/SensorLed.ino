int SENSOR = 2;
int VALOR;
int ANTERIOR = 1;
int LEDROJO = 9;
int LEDVERDE = 10;
int LEDAZUL = 11;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
}

void loop() {
  VALOR = digitalRead(SENSOR);
  if (VALOR == HIGH){
    analogWrite(LEDROJO, 0);
    analogWrite(LEDVERDE, 255);
    analogWrite(LEDAZUL, 0);
  }
  else{
    analogWrite(LEDROJO, 255);
    analogWrite(LEDVERDE, 0);
    analogWrite(LEDAZUL, 0);    
  }
}
