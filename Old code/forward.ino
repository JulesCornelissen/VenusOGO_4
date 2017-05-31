#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
 Serial.begin(9600);
 Serial.println("===Begin===");
 servoLeft.attach(13);
 servoRight.attach(12);
}

void loop() {
int x = 15;
int count = 0;
int state = digitalRead(7);
servoLeft.writeMicroseconds(1700);
servoRight.writeMicroseconds(1300);
while(count<x)
  {
    if(state != digitalRead(7))
      {
        state = digitalRead(7);
        count ++;
        Serial.println(" ");
        Serial.println(count);
        Serial.println(" ");
      }
  {
}

}
Serial.println("Out of the loop");
Serial.print("The count equals: ");
Serial.println(count);
servoLeft.detach();
servoRight.detach();
delay(10000);
}
