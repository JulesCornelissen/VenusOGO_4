#include <Wire.h>

int deviceNumber = 5; //Fill in the number that's set on the micro (device address)

int leftDistance = 0;
int centerDistance = 0;
int rightDistance = 0;

boolean leftCNY = true;
boolean centerCNY = true;
boolean rightCNY = true;

int leftBeacon = 0;
int centerBeacon = 0;
int rightBeacon = 0;

void setup() {
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
  int g=0;
  for (g=0; g<=i; g++){
    Serial.print(recv[g]);
  }
  Serial.print("\t");
  recv[i] = '\0'; // Null terminate the array as to avoid any potential problems.
  switch (recv[0]){
    case 0:    //receive left Sharp distance sensor -- distance in mm
    leftDistance = atoi(&recv[1]);
    break;
    case 1:   //receive center Sharp distance sensor -- distance in mm
    centerDistance = atoi(&recv[1]);
    break;
    case 2:   //receive right Sharp distance sensor -- distance in mm
    rightDistance = atoi(&recv[1]);
    break;
    case 3:   //receive left CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      leftCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      leftCNY = false;
    }
    break;
    case 4:   //receive center CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      centerCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      centerCNY = false;
    }
    break;
    case 5:   //receive right CNY70 sensor 1 = high (no tape) - 0 = low (there's something, probably tape)
    if (recv[i-1] == '1'){ //check the last digit of the data received, 1 means boolean should be true and 0 means the boolean should be false
      rightCNY = true;
    }
    else if (recv[i-1] == '0'){ //Make sure to check if the digit is actually zero instead of a different random value in case of wrong communication
      rightCNY = false;
    }
    break;
    case 6:   //receive left beacon sensor - which beacon(s) it detects
    leftBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    case 7:   //receive center beacon sensor - which beacon(s) it detects
    centerBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    case 8:   //receive right beacon sensor - which beacon(s) it detects
    rightBeacon = atoi(&recv[i-3]); // grab the last two digits (i-3 because i is 1 larger than the array size) it received which is enough to represent up to 20 possibilities
    break;
    case 9:   //unused
      break;
  }
}

void loop() {

}
