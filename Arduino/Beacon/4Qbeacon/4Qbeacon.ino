/* send.ino Example sketch for IRLib2
 *  Illustrates how to send a code.
 */
#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.

IRsend mySender;

void setup() {
  pinMode(2,OUTPUT);  //q1
  pinMode(3,OUTPUT);  //q2
  pinMode(4,OUTPUT);  //q3
  pinMode(6,OUTPUT);  //q4
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(6,LOW);

}

void loop() {

  digitalWrite(2, HIGH);
  delay(10);                      
mySender.send(NEC,0x61a0f00f,0);//NEC TV power button=0x61a0f00f
  delay(10);    
  digitalWrite(2, LOW);
  
  digitalWrite(3, HIGH);
  delay(10);                      
mySender.send(NEC,0x61a0e00e,0);//NEC TV power button=0x61a0f00f
  digitalWrite(3, LOW);
  
  digitalWrite(4, HIGH);
  delay(10);                      
mySender.send(NEC,0x61a0d00d,0);//NEC TV power button=0x61a0f00f
  digitalWrite(4, LOW);
  
  digitalWrite(6, HIGH);
  delay(10);                      
mySender.send(NEC,0x61a0c00c,0);//NEC TV power button=0x61a0f00f
  digitalWrite(6, LOW);
}
