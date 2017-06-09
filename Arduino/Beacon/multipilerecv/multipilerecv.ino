/* dump.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.
#include "IRLibAll.h"

IRrecvPCI recvOne(0); //create receiver and pass pin number
IRrecvPCI recvTwo(1); //create second receiver
IRrecvPCI recvThree(7); //create third receiver
IRdecode myDecoder;   //create decoder

uint32_t IRValueOne;
uint32_t IRValueTwo;
uint32_t IRValueThree;
  
void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  recvOne.enableIRIn(); // Start the receiver
  recvTwo.enableIRIn(); // Start second receiver
  recvThree.enableIRIn(); // Start third receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
     /*
     * Change these three functions to compare the data and then output
     * which quadrant it's actually in. 
     */
  if (recvOne.getResults()) {
    Serial.println(F("---------------------------------------\n RECEIVER ONE \n---------------------------------------"));
    //myDecoder.decode();           //Decode it
    //myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    IRValueOne = myDecoder.value; //Store the received value in a 32bit integer
    recvOne.enableIRIn();     //Restart receiver
  }
  if (recvTwo.getResults()) {
    Serial.println(F("---------------------------------------\n RECEIVER TWO \n---------------------------------------"));
    //myDecoder.decode();           //Decode it
    //myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    IRValueTwo = myDecoder.value; //Store the received value in a 32bit integer
    recvTwo.enableIRIn();     //Restart receiver
  }
  if (recvThree.getResults()) {
    Serial.println(F("---------------------------------------\n RECEIVER THREE \n---------------------------------------"));
    //myDecoder.decode();           //Decode it
    //myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    IRValueThree = myDecoder.value; //Store the received value in a 32bit integer
    recvThree.enableIRIn();   //Restart receiver
  }
}

