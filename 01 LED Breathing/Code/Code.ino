// This program creates a smooth fading effect on an LED connected to digital pin 9.
// The LED's brightness increases from off to maximum and then decreases back to off repeatedly.

#define LED_1_PIN 9  // Define digital pin 9 for the LED

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);  // Set the LED pin as an output
}

void loop()
{
  // Gradually increase the brightness from 0 to 255
  for(int i = 0; i <= 255; i++){
    analogWrite(LED_1_PIN, i);  // Set the LED brightness level
    delay(10);                  // Wait for 10 milliseconds
  }
  
  // Gradually decrease the brightness from 255 to 0
  for(int i = 255; i >= 0; i = i - 1){
    analogWrite(LED_1_PIN, i);  // Set the LED brightness level
    delay(10);                  // Wait for 10 milliseconds
  }
  
  // The code below switches the LED from low to high
  // and back down to low without any gradient effect.
  /*
  analogWrite(LED_1_PIN, 0);    // Turn off the LED
  delay(500);                   // Wait for 500 milliseconds
  analogWrite(LED_1_PIN, 255);  // Turn on the LED at maximum brightness
  delay(500);                   // Wait for 500 milliseconds
  */
}
