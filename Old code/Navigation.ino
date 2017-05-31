#include <Servo.h>

Servo ServoLeft;
Servo ServoRight;
int Rightturn = true;
int UnitLengt = 15;
int Factor = 1;
int TurnCount = 7;
//int Initialstep = true;


void setup()
{
    // put your setup code here, to run once:


    TurnCount = 1;
}

void loop()
{
    next_stage();
    turn();
    forward();
    turn();
    Factor = 2*Factor;
    forward();
    Factor = Factor/2;
    turn();
    forward();
    turn();
    Factor++;
}

void next_stage()
{
    int Count = 0;
    int state = digitalRead(7);
    ServoLeft.writeMicroseconds(1700);
    ServoRight.writeMicroseconds(1300);
    while(Count<UnitLengt)
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

void forward()
{
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
    if(TurnCount%4 ==0)
    {
        Rightturn = !Rightturn;
    }
    switch(Rightturn)
    {
    case 0:
    {
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
}

