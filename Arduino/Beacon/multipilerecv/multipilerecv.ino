/* dump.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.
#include "IRLibAll.h"

IRrecvPCI recvOne(7); //create receiver and pass pin number
IRrecvPCI recvTwo(3); //create second receiver on pin 3
IRdecode myDecoder;   //create decoder

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  recvOne.enableIRIn(); // Start the receiver
  recvTwo.enableIRIn(); // start second receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (recvOne.getResults()) {
    Serial.println(F("---------------------------------------\n RECEIVER ONE \n---------------------------------------"));
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    recvOne.enableIRIn();      //Restart receiver
  }
  if (recvTwo.getResults()) {
    Serial.println(F("---------------------------------------\n RECEIVER TWO \n---------------------------------------"));
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    recvTwo.enableIRIn();      //Restart receiver
  }
}

