#define LED_1_PIN 9
void setup()
{
  pinMode(LED_1_PIN, OUTPUT);
}

void loop()
{
  for(int i = 0; i <= 255; i++){
    analogWrite(LED_1_PIN, i);
    delay(10);
  }
  for(int i = 255; i >= 0; i = i - 1){
    analogWrite(LED_1_PIN, i);
    delay(10);
  }
  
  // The code below switches the LED from low to high
  // and back down to low without any gradient effect.
  /* analogWrite(LED_1_PIN, 0);
  delay(500); 
  analogWrite(LED_1_PIN, 255);
  delay(500); */
}