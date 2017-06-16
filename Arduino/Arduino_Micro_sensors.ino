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

// void sendBoolean(bool condition){
// Wire.beginTransmission(9);
//   Wire.write(condition);
//   Wire.endTransmission();


void sendData(int data){
   Wire.beginTransmission(5); // transmit to device #9
   Wire.write(data); // sends data 
   Wire.endTransmission();    // stop transmitting
  
}

void loop() {
  if (digitalRead(4) == LOW){
    int CNY_left = 30;
    sendData(CNY_left); 
  }
  else if (digitalRead(4) == HIGH){
    int CNY_left = 31;
    sendData(CNY_left);
  }

  

  if (digitalRead(5) == LOW){
    int CNY_right = 30;
    sendData(CNY_right); 
  }
  else if (digitalRead(5) == HIGH){
    int CNY_right = 31;
    sendData(CNY_right);
  }



  if (digitalRead(6) == LOW){
    int CNY_center = 30;
    sendData(CNY_center); 
  }
  else if (digitalRead(6) == HIGH){
    int CNY_center = 31;
    sendData(CNY_center);
  }
  
  
 
 
  
  delay(500);
}

