void setup()
{
  pinMode(6, OUTPUT);
}

void loop()
{
  digitalWrite(6, HIGH);
  delayMicroseconds(5); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(6, LOW);
  delayMicroseconds(5);
}
