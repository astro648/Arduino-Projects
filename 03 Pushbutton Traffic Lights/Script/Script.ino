// This program controls three LEDs connected to digital pins 9, 10, and 11,
// and a pushbutton connected to digital pin 2.
// When the pushbutton is pressed, the LEDs light up in a specific sequence.

#define LED_1_PIN 11        // Define digital pin 11 for LED 1
#define LED_2_PIN 10        // Define digital pin 10 for LED 2
#define LED_3_PIN 9         // Define digital pin 9 for LED 3
#define PUSHBUTTON_PIN 2    // Define digital pin 2 for the pushbutton

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);      // Set LED 1 pin as an output
  pinMode(LED_2_PIN, OUTPUT);      // Set LED 2 pin as an output
  pinMode(LED_3_PIN, OUTPUT);      // Set LED 3 pin as an output
  pinMode(PUSHBUTTON_PIN, INPUT);  // Set pushbutton pin as an input
}

void loop()
{
  // Loop to control the sequence of LEDs based on button presses
  for(int i = 1; i <= 3; i = i){
    // Check if the pushbutton is pressed and the sequence is at step 1
    if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 1){
      digitalWrite(LED_3_PIN, LOW);    // Turn off LED 3
      digitalWrite(LED_1_PIN, HIGH);   // Turn on LED 1
      delay(100);                      // Wait for 100 milliseconds
      i++;                             // Move to the next step in the sequence
    }
    // Check if the pushbutton is pressed and the sequence is at step 2
    else if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 2){
      digitalWrite(LED_2_PIN, HIGH);   // Turn on LED 2
      digitalWrite(LED_1_PIN, LOW);    // Turn off LED 1
      delay(100);                      // Wait for 100 milliseconds
      i++;                             // Move to the next step in the sequence
    }
    // Check if the pushbutton is pressed and the sequence is at step 3
    else if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 3){
      digitalWrite(LED_3_PIN, HIGH);   // Turn on LED 3
      digitalWrite(LED_2_PIN, LOW);    // Turn off LED 2
      delay(100);                      // Wait for 100 milliseconds
      i++;                             // Increment i to exit the loop
    }
  }
}
