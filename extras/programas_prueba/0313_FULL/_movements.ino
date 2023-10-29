float x = 0;

void motor_foward_left_run(int16_t speed)
{
   motor_10.run(-speed);
}

void motor_foward_right_run(int16_t speed)
{
  motor_1.run(speed);
}

void motor_back_left_run(int16_t speed)
{
  motor_2.run(-speed);
}

void motor_back_right_run(int16_t speed)
{
  motor_9.run(speed);
}

void move_control(int16_t vx, int16_t vy, int16_t vw)
{
  int16_t foward_left_speed;
  int16_t foward_right_speed;
  int16_t back_left_speed;
  int16_t back_right_speed;

  foward_left_speed = vy + vx + vw;
  foward_right_speed = vy - vx - vw;
  back_left_speed = vy - vx + vw;
  back_right_speed = vy + vx - vw;

  motor_foward_left_run(foward_left_speed);
  motor_foward_right_run(foward_right_speed);
  motor_back_left_run(back_left_speed);
  motor_back_right_run(back_right_speed);
}

int velocidad = 90;

void forward(int16_t speed){
  move_control(0, speed / 100.0 * 255, 0);
}

void backward(int16_t speed){
  move_control(0, -speed / 100.0 * 255, 0); 
}

void turnright(int16_t speed){
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);
}

void turnleft(int16_t speed){
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);
}

void turn90right(int16_t speed){ // giro 90 a derechas perfecto para speed = 25 en giro
  forward(20);
  _delay(0.35);  
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);            
  _delay(1.05);
}

void turn90left(int16_t speed){  // giro 90 a izquierdas perfecto para speed = 25 en giro
  forward(20);
  _delay(0.35);  
  motor_1.run(speed / 100.0 * 255);
  motor_9.run(speed / 100.0 * 255);
  motor_2.run(speed / 100.0 * 255);
  motor_10.run(speed / 100.0 * 255);            
  _delay(1.05);
}

void parar(int16_t speed){
  motor_1.run(0);
  motor_9.run(0);
  motor_2.run(0);
  motor_10.run(0);
}

void turnaround(int16_t speed) {  // para vuelta 180 grados velocidad a 30
  forward(30);
  _delay(0.5);  
  motor_1.run(-speed / 100.0 * 255);
  motor_9.run(-speed / 100.0 * 255);
  motor_2.run(-speed / 100.0 * 255);
  motor_10.run(-speed / 100.0 * 255);
  _delay(1.75);
}

void readAllSensors() {
  forward(25);
  _delay(0.05);
  parar(0);
  _delay(0.05);
}
