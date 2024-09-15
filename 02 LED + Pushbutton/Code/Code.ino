// This program controls an LED connected to digital pin 9 using a pushbutton connected to digital pin 2.
// When the pushbutton is pressed, the LED turns on; when the pushbutton is released, the LED turns off.

#define LED_1_PIN 9          // Define digital pin 9 for the LED
#define PUSHBUTTON_PIN 2     // Define digital pin 2 for the pushbutton

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);       // Set the LED pin as an output
  pinMode(PUSHBUTTON_PIN, INPUT);   // Set the pushbutton pin as an input
}

void loop()
{
  // Check the state of the pushbutton
  if(digitalRead(PUSHBUTTON_PIN) == HIGH){
    digitalWrite(LED_1_PIN, HIGH);  // If the pushbutton is pressed, turn on the LED
  } else {
    digitalWrite(LED_1_PIN, LOW);   // If the pushbutton is not pressed, turn off the LED
  }
}
