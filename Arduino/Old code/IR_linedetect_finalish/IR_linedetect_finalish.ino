#include <Servo.h>
#include <math.h>

//SERVO PINS
#define ULTRA_SERVO 10
#define LEFT_SERVO 12
#define RIGHT_SERVO 13

//SENSOR PINS
#define LDLEFT_PIN A0
#define LDCENTER_PIN A1
#define LDRIGHT_PIN A2
#define ULTRA_PIN 9

//CONSTANTS
#define IR_BOUNDARY 600 //Threshold 0-1023
#define ULTRA_BOUNDARY 14.5 //unit: centrimetres

//SETUP
Servo servo_left, servo_right, servo_ultra;

void setup(){
    Serial.begin(9600);
    servo_ultra.attach(ULTRA_SERVO);
    servo_left.attach(LEFT_SERVO);
    servo_right.attach(RIGHT_SERVO);
    servo_ultra.write(90);
    
    pinMode(LDLEFT_PIN, INPUT);
    pinMode(LDCENTER_PIN, INPUT);
    pinMode(LDRIGHT_PIN, INPUT);
}

void forward(){
    servo_left.writeMicroseconds(1300);
    servo_right.writeMicroseconds(1700);
}

void reverse(){
    servo_left.writeMicroseconds(1700);
    servo_right.writeMicroseconds(1300);
}

void stop(){
    servo_left.writeMicroseconds(1500);
    servo_right.writeMicroseconds(1500);
}

void rotate(double angle){
    servo_left.writeMicroseconds(1500 + 200*(angle>0?1:-1));
    servo_right.writeMicroseconds(1500 + 200*(angle>0?1:-1));
    delay(round(angle * 7.78));
}

bool rotate_until(int pin, bool (*condition)(int), bool right){
    bool flag = false;
    while ((*condition)(pin)){
        servo_left.writeMicroseconds(1500 + 200*(right?1:-1));
        servo_right.writeMicroseconds(1500 + 200*(right?1:-1));
        flag = true;
    }
    return flag;
}

void turn_right(){ 
   rotate(90);
}

void turn_left(){
    rotate(-90);
}

unsigned long ping_cm(){
    pinMode(ULTRA_PIN, OUTPUT);
    digitalWrite(ULTRA_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRA_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(ULTRA_PIN, LOW);
    pinMode(ULTRA_PIN, INPUT);
    digitalWrite(ULTRA_PIN, HIGH);
    unsigned long result = (pulseIn(ULTRA_PIN, HIGH) / 58.138);
    return result;
}

bool pick_direction(){
    stop();
    servo_ultra.write(0);
    delay(1000);
    unsigned long ping_left = ping_cm();
    servo_ultra.write(180);
    delay(1000);
    unsigned long ping_right = ping_cm();
    servo_ultra.write(90);
    return (ping_left < ping_right);
}

bool LD_condition(int pin){
    return analogRead(pin) < IR_BOUNDARY;
}

void loop(){
    if (LD_condition(LDLEFT_PIN) &&
         LD_condition(LDRIGHT_PIN) &&
         LD_condition(LDCENTER_PIN)){ 
        pick_direction() ? turn_right() : turn_left();
    } else {
        rotate_until(LDLEFT_PIN, &LD_condition, true);
        rotate_until(LDRIGHT_PIN, &LD_condition, false);
    }
    forward();
    
}
