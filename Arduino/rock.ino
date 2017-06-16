void setup() {
  Serial.begin(9600);
  pinMode(A5,INPUT);
  pinMode(A4,INPUT);
  Serial.println("====Begin====");
  }

void loop() {
  Serial.println(A4);
  delay(1000);
  Serial.println(A5);
  delay(1000);
  double left_sensor  = 1/((analogRead(A4)+1) * 5/1023) - 0.42;
  double right_sensor = 1/((analogRead(A5)+1) * 5/1023) - 0.42;
  Serial.println("The distance to the left: ");
  Serial.println(left_sensor);
  Serial.println("The distance to the rightt: ");
  Serial.println(right_sensor);
  }
  
