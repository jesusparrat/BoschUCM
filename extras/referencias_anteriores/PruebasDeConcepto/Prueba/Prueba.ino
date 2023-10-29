int ENA = 11;
int IN1D = A1;
int IN2D = A2;
int IN1I = A3;
int IN2I = A4;
int ENB = 10;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1D, OUTPUT);
  pinMode(IN2D, OUTPUT);
  pinMode(IN1I, OUTPUT);
  pinMode(IN2I, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void loop() {
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);
}
