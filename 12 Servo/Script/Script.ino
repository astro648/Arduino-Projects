#include<Servo.h>

Servo sr;

int val;

void setup()
{
  sr.attach(9);
}

void loop()
{
  for (int i=0; i<=180; i++){
    sr.write(i);
    delay(10);
  }
  
  for (int j=180; j>=0; j--){
    sr.write(j);
    delay(10);
  }
  
  delay(500);
}