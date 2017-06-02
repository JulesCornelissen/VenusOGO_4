
 
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin)); 
    PCIFR  |= bit (digitalPinToPCICRbit(pin));
    PCICR  |= bit (digitalPinToPCICRbit(pin)); 
}
 
ISR (PCINT0_vect)
 {    
     digitalWrite(13,HIGH);
 }

 
void setup() {  
int i;
 
  for (i=0; i<=12; i++)
      digitalWrite(i,HIGH);  
 
  for (i=A0; i<=A5; i++)
      digitalWrite(i,HIGH);
 
  pinMode(13,OUTPUT);  // LED
 
  pciSetup(7);
  pciSetup(8);
  pciSetup(9);
  pciSetup(A0);
}
 
 
void loop() {
  // Nothing needed
}
