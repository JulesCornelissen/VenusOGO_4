#include <Servo.h>

//Servo pin definitions
#define SERVO_PIN 10
#define LEFT_PIN 12
#define RIGHT_PIN 13

//IO pin definitions
#define ULTRA_PIN 9

//Servos
Servo servo_left;
Servo servo_right;
Servo servo_ultra;

void setup(){
  Serial.begin(9600);
  servo_left.attach(LEFT_PIN);
  servo_right.attach(RIGHT_PIN);
  servo_ultra.attach(SERVO_PIN);
  servo_ultra.write(90);
}

void forward(){
  servo_left.writeMicroseconds(1300);
  servo_right.writeMicroseconds(1700);
}

void turn_right(){
  servo_left.writeMicroseconds(1700);
  servo_right.writeMicroseconds(1700);
  delay(700);
}

void turn_left(){
  servo_left.writeMicroseconds(1300);
  servo_right.writeMicroseconds(1300);
  delay(700);
}

void stop(){
  servo_left.writeMicroseconds(1500);
  servo_right.writeMicroseconds(1500);
}

unsigned long ping_inches()
{
  pinMode(ULTRA_PIN, OUTPUT);
  digitalWrite(ULTRA_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(ULTRA_PIN, LOW);
  pinMode(ULTRA_PIN, INPUT);
  digitalWrite(ULTRA_PIN, HIGH);
  return (pulseIn(ULTRA_PIN, HIGH) / 58.138) * 0.39;
}

boolean pick_direction(){
  stop();
  servo_ultra.write(0);
  delay(1000);
  unsigned long ping_left = ping_inches();
  servo_ultra.write(180);
  delay(1000);
  unsigned long ping_right = ping_inches();
  servo_ultra.write(90);
  return (ping_left > ping_right);
}

void loop(){
  forward();
  delay(250);
  if (ping_inches() < 5.5){
    pick_direction() ? turn_left() : turn_right();
  }
}
