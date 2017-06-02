#include <Servo.h>
#include <math.h>

//SERVO PINS
#define ULTRA_SERVO 10
#define LEFT_SERVO 12
#define RIGHT_SERVO 13
#define GRABBER_SERVO 11

//SENSOR PIN
#define LEFT_ENCODER 7
#define RIGHT_ENCODER 8

#define ULTRA_PIN 9
#define sensor_FRONT A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_LEFT A4
#define sensor_RIGHT A5

//SERVOS
Servo servo_left;
Servo servo_right;
Servo servo_ultra;
Servo servo_grabber;

unsigned long dist_left, dist_right;

/* INTERRUPT CALLBACKS */

void increment_left_dist(){ dist_left++; }

void increment_right_dist(){ dist_right++; }

double left_distance(){
    return dist_left * 1.30666692444;
}

double right_distance(){
    return dist_right * 1.30666692444;
}

/* */

void setup(){
    servo_left.attach(LEFT_SERVO);
    servo_right.attach(RIGHT_SERVO);
    servo_ultra.attach(ULTRA_SERVO);
    servo_ultra.write(90);
    
    servo_grabber.attach(GRABBER_SERVO);
    servo_grabber.write(180);
    
    pinMode(LEFT_ENCODER, INPUT);
    attachInterrupt(LEFT_ENCODER, increment_left_dist, CHANGE);
    
    pinMode(RIGHT_ENCODER, INPUT);
    attachInterrupt(RIGHT_ENCODER, increment_right_dist, CHANGE);
    
    Serial.begin(9600);
}

void forward(){
    servo_left.writeMicroseconds(1300);
    servo_right.writeMicroseconds(1700);
}

void forward_dist(double dist){
    double start_left = left_distance();
    double start_right = right_distance();
    while (((left_distance() - start_left) + (right_distance() - start_right)) / 2 < dist){
        forward();
    }
    stop();
}

void reverse(){
    servo_left.writeMicroseconds(1700);
    servo_right.writeMicroseconds(1300);
}

void reverse_dist(double dist){
    double start_left = left_distance();
    double start_right = right_distance();
    while (((left_distance() - start_left) + (right_distance() - start_right)) / 2 < dist){
        reverse();
    }
    stop();
}

void stop(){
    servo_left.writeMicroseconds(1500);
    servo_right.writeMicroseconds(1500);
}

void rotate_right(){
    servo_left.writeMicroseconds(1700);
    servo_right.writeMicroseconds(1700);
}

void turn_right(){ 
    rotate_right();
    delay(700);
    stop();
}

void rotate_left(){
    servo_left.writeMicroseconds(1300);
    servo_right.writeMicroseconds(1300);
}

void turn_left(){
    rotate_left();
    delay(700);
    stop();
}

double ping_centim(){
    pinMode(ULTRA_PIN, OUTPUT);
    digitalWrite(ULTRA_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRA_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(ULTRA_PIN, LOW);
    pinMode(ULTRA_PIN, INPUT);
    digitalWrite(ULTRA_PIN, HIGH);
    return (pulseIn(ULTRA_PIN, HIGH) / 58.138);
}

double distance_front(){
    double voltage = analogRead(sensor_FRONT)*0.0048828125;
    return (13*pow(voltage, -1));
}

double distance_left(){
    double voltage = analogRead(sensor_LEFT)*0.0048828125;
    return (13*pow(voltage, -1));
}

double distance_right(){
    double voltage = analogRead(sensor_RIGHT)*0.0048828125;
    return (13*pow(voltage, -1));
}

void pick_rock(){
    stop();
    servo_grabber.write(90);
    delay(1000);
}

void reach_rock() {
    double front_rock = distance_front();
    double left_rock = distance_left();
    double right_rock = distance_right();
    double ultra = ping_centim();
    
    if (front_rock < 5){
        pick_rock();
    } else if (15 < left_rock || left_rock < 30){
        while (distance_front > 30){
            rotate_left();
        }
    } else if (15 < right_rock || right_rock < 30){
        while (distance_front > 30){
            rotate_right();
        }
    } else if (left_rock <= 15){
        reverse_dist(sqrt(900 - pow(left_rock, 2)));
    } else if (right_rock <= 15){
        reverse_dist(sqrt(900 - pow(right_rock, 2)));
    }
}

void loop(){
    forward();

    reach_rock();
   
}

