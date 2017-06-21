#include <Wire.h>
#include <Servo.h>
#include <math.h>
#include "IRLibAll.h"

//SENSOR PINS
#define LDLEFT_PIN 4 // IR line/rock detection CNY70 sensors
#define LDCENTER_PIN 6
#define LDRIGHT_PIN 5

#define sensor_FRONT A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_LEFT A1
#define sensor_RIGHT A2

IRrecvPCI recvOne(0); //create receiver and pass pin number
IRrecvPCI recvTwo(1); //create second receiver
IRrecvPCI recvThree(7); //create third receiver
IRdecode myDecoder;   //create decoder

uint32_t IRValueOne;
uint32_t IRValueTwo;
uint32_t IRValueThree;

bool LD_condition(int pin){
  return digitalRead(pin) == HIGH;
}

void setup(){
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  recvOne.enableIRIn(); // Start the receiver;//
  recvTwo.enableIRIn(); // Start second receiver
  recvThree.enableIRIn(); // Start third receiver
  Serial.println(F("Ready to receive IR signals"));
  
  pinMode(LDLEFT_PIN, INPUT);
  pinMode(LDCENTER_PIN, INPUT);
  pinMode(LDRIGHT_PIN, INPUT);
}

int distance_front(){
    double voltage = analogRead(sensor_FRONT)*0.0048828125;
    return (13*pow(voltage, -1));
}

int distance_left(){
    double voltage = analogRead(sensor_LEFT)*0.0048828125;
    return (13*pow(voltage, -1));
}

int distance_right(){
    double voltage = analogRead(sensor_RIGHT)*0.0048828125;
    return (13*pow(voltage, -1));
}

int sharp_left = distance_left();
int sharp_right = distance_right();
int sharp_front = distance_front();

void sendData(char data[]){
   Wire.beginTransmission(5); // transmit to device #5
   Wire.write(data); // sends data 
   Wire.endTransmission();    // stop transmitting
   Serial.println(data);
   Serial.println("Sent data!");
}

void loop() {
  char distance_left[];
  char distance_center[];
  char distance_right[];

  char CNY_left[];
  char CNY_center[];
  char CNY_right[];
  
  if (digitalRead(4) == LOW){
    CNY_left[] = "40"; //Tape detected by the left CNY70
    sendData(CNY_left); 
  }
  else if (digitalRead(4) == HIGH){
    char CNY_left[] = "41"; //No tape detected by the left CNY70
    sendData(CNY_left);
  }
  if (digitalRead(6) == LOW){
    char CNY_center[] = "50"; //Tape detected by the left CNY70
    sendData(CNY_center); 
  }
  else if (digitalRead(6) == HIGH){
    char CNY_center[] = "51"; //No tape detected by the left CNY70
    sendData(CNY_center);
  }  
  if (digitalRead(5) == LOW){
    char CNY_right[] = "60"; //Tape detected by the left CNY70
    sendData(CNY_right); 
  }
  else if (digitalRead(5) == HIGH){
    char CNY_right[] = "61"; //No tape detected by the left CNY70
    sendData(CNY_right);
  }

  if (analogRead(19) > 100 ){ // Left distance
    distance_left[] = "11"; // Rock is to the left of the robot
  }
  else{
    distance_left[] = "10"; // There is no rock to the left of the robot
  }

  if (analogRead(19) > 100 && analogRead(19) < 450 ){ // Center distance
    distance_right[] = "21"; // rock in front of the grabber
  }
  else{
    if (analogRead(19) > 450){
      distance_right[] = "22"; // rock is inbetween the grabber
    }
    else{
    distance_right[] = "20"; // no rock detected
    }
  }
  
  if (analogRead(19) > 100 ){ // Right distance
    distance_right[] = "31"; // Rock is to the right of the robot
  }
  else{
    distance_right[] = "30"; // There is no rock to the right of the robot
  }
  
  //delay(500);
}

