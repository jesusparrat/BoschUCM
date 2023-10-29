int ENA = A0;
int IN1D = A1;
int IN2D = A2;
int IN1I = A3;
int IN2I = A4;
int ENB = A5;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1D, OUTPUT);
  pinMode(IN2D, OUTPUT);
  pinMode(IN1I, OUTPUT);
  pinMode(IN2I, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);  
}


void recta(int tiempo){  
  digitalWrite(IN1D, LOW);
  digitalWrite(IN2D, HIGH);  
  digitalWrite(IN1I, HIGH);
  digitalWrite(IN2I, LOW);
  delay(tiempo);
}

void noventagrados(bool derecha){
  if(derecha){  
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, HIGH);  
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH); 
  }
  else {      
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);  
    digitalWrite(IN1I, HIGH);
    digitalWrite(IN2I, LOW);   
  }
  delay(230);  
}

void cientoochentagrados(){
  digitalWrite(IN1D, LOW);
  digitalWrite(IN2D, HIGH);  
  digitalWrite(IN1I, LOW);
  digitalWrite(IN2I, HIGH);  
  delay(460);  
}

void parada(int tiempo){
  digitalWrite(IN1D, LOW);
  digitalWrite(IN2D, LOW);  
  digitalWrite(IN1I, LOW);
  digitalWrite(IN2I, LOW);
  delay(tiempo);  
}

void loop() {
  parada(2000);
  recta(1000);
  parada(2000);
  noventagrados(true);
  parada(2000);
  recta(1000);
  parada(2000);
  noventagrados(false);
  parada(2000);
  recta(1000);
  parada(2000);
  cientoochentagrados();  
  recta(2000);
  parada(2000);
}
