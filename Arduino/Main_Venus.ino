int Flag_R = 0;
int Flag_A = 0;
int Flag_P = 0;
int Flag_N = 0;
int Flag_AC= 0;
int Flag_AM= 0;
int Rightturn = true;
int UnitLengt = 15;
int Factor = 1;
int TurnCount = 7;
int corner = 1;

void setup() {
  // put your setup code here, to run once:

}

void loop() 
{
  navigate();
  avade();
  pick_up();
  return_to_base(); 
 }

 void navigate()
 {
  while(Flag_N == 1)
  {
    next_stage();
    turn();
    forward();
    turn();
    forward();
    turn();
    Factor++;
  }
  
 }
 void forward()
{
    Serial.println("We in the forward stage");
    int Count = 0;
    int state = digitalRead(7);
    ServoLeft.writeMicroseconds(1700);
    ServoRight.writeMicroseconds(1300);
    while(Count<Factor*UnitLengt)
    {
        if(state != digitalRead(7))
        {
            state = digitalRead(7);
            Count ++;
            Serial.println(" ");
            Serial.println(Count);
            Serial.println(" ");
        }

    }
}


void turn()
{
    if(corner%3 ==0)
    {
        Rightturn = !Rightturn;
    }
    switch(Rightturn)
    {
    case 0:
    {
        Serial.println("We in the turn left part");
        int Count = 0;
        ServoLeft.writeMicroseconds(1300);
        ServoRight.writeMicroseconds(1300);
        int state = digitalRead(7);
        while(Count < TurnCount)
        {
            if(state != digitalRead(7))
            {
                state = digitalRead(7);
                Count++;
                Serial.println(" ");
                Serial.println(Count);
                Serial.println(" ");
            }
        }
        Serial.println("Out of the loop");
        Serial.print("The Count equals: ");
        Serial.println(Count);
        break;
    }
    case 1:
    {
        Serial.println("We in the turn right part");
        int Count = 0;
        ServoLeft.writeMicroseconds(1700);
        ServoRight.writeMicroseconds(1700);
        int state = digitalRead(7);
        while(Count < TurnCount)
        {
            if(state != digitalRead(7))
            {
                state = digitalRead(7);
                Count++;
                Serial.println(" ");
                Serial.println(Count);
                Serial.println(" ");
            }
        }
        Serial.println("Out of the loop");
        Serial.print("The Count equals: ");
        Serial.println();
        break;
    }
    }
    corner++; 
}

  
