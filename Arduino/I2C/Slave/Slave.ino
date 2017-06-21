#include <Wire.h>

int deviceNumber = 5; //Fill in the number that's set on the micro (device address)

boolean leftDistance = 0;
int centerDistance = 0;
boolean rightDistance = 0;

boolean leftCNY = true;
boolean centerCNY = true;
boolean rightCNY = true;

int leftBeacon = 0;
int centerBeacon = 0;
int rightBeacon = 0;

void setup() {
//  Serial.begin(9600);
//  delay(2000); while (!Serial); //delay for Leonardo
//  Serial.println("Ready for serial");
  Wire.begin(deviceNumber); //Open I2C communication bus on previously specified address
  Wire.onReceive(I2CRead); // Run this function upon interrupt from I2C communication
}

void I2CRead(int numBytes) {
  char recv[8];
  int i=0;
  while(Wire.available()){
    recv[i] = Wire.read(); // Read the incoming data over I2C byte-by-byte and store them in to seperate positions in an array of characters
    i++;
  }
  recv[i] = '\0'; // Null terminate the array as to avoid any potential problems.
  
  int switchInt = atoi(&recv[0]); // Convert from string to int for switch case
  while (switchInt >= 10){
    switchInt /= 10; //Keep dividing the total number by ten until it is no longer possible to do so, this gets use the first digit of this integer.
  }
  
  switch (switchInt){
    case 1:    //receive left Sharp distance sensor -- distance in mm
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      leftDistance = true; // True means that the sensor detects a rock in front of the robot
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      leftDistance = false; // False means that the sensor does not detect a rock
    }
    break;
    
    case 2:   //receive center Sharp distance sensor
      switch (recv[i-1]){ //for the center sensor there's a special case, the rock can be in front of the robot (1) and the rock can be in between the grabbber (2)
        case 0:
        centerDistance = 0; // The censor doesn't detect any rock
        break;
        case 1:
        centerDistance = 1; // The sensor detects a rock in front of the robot
        break;
        case 2:
        centerDistance = 2; // The sensor detects a rock in between the grabber
        break;
      }
    break;
    
    case 3:   //receive right Sharp distance sensor -- distance in mm
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      rightDistance = true; // True means that the sensor detects a rock in front of the robot
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      rightDistance = false; // False means that the sensor does not detect a rock
    }
    break;
    
    case 4:   //receive left CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      leftCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      leftCNY = false;
    }
    break;
    
    case 5:   //receive center CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      centerCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      centerCNY = false;
    }
    break;
    
    case 6:   //receive right CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      rightCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      rightCNY = false;
    }
    break;
    
    case 7:   //receive left beacon sensor - which beacon(s) it detects
    leftBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    
    case 8:   //receive center beacon sensor - which beacon(s) it detects
    centerBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    
    case 9:   //receive right beacon sensor - which beacon(s) it detects
    rightBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    
    case 0:   //unused
    break;
  }
}

void loop() {

}
