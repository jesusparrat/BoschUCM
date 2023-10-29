int sensor = 2;
int LEDROJO = 11;
int LEDAZUL = 10;
int LEDVERDE = 9;
int valor;

int IN1 = 7;
int IN2 = 8;
int EMA = 5;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ema, OUTPUT);
  
  pinMode(sensor, INPUT);
  
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  
}

void loop() {
  valor = digitalRead(sensor);

  if(valor == 1){
    analogWrite(LEDROJO, 0);
    analogWrite(LEDVERDE, 255);
    analogWrite(LEDAZUL, 0);
    
    digitalWrite(EMA, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);    
  }
  else {
    analogWrite(LEDROJO, 255);
    analogWrite(LEDVERDE, 0);
    analogWrite(LEDAZUL, 0);
      
    digitalWrite(EMA, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }  
}
