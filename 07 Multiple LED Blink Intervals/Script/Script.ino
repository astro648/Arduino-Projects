// This program controls three LEDs connected to digital pins 10, 11, and 12.
// Each LED blinks independently at different intervals specified in milliseconds.

#define LED_1_PIN 12  // Define digital pin 12 for LED 1
#define LED_2_PIN 11  // Define digital pin 11 for LED 2
#define LED_3_PIN 10  // Define digital pin 10 for LED 3

// Variables to keep track of the timing for each LED
unsigned long previousTimeLED1Blink = millis(); // Store the last toggle time for LED 1
unsigned long timeIntervalLED1Blink = 470;      // Set blink interval for LED 1 (470 ms)

unsigned long previousTimeLED2Blink = millis(); // Store the last toggle time for LED 2
unsigned long timeIntervalLED2Blink = 900;      // Set blink interval for LED 2 (900 ms)

unsigned long previousTimeLED3Blink = millis(); // Store the last toggle time for LED 3
unsigned long timeIntervalLED3Blink = 1300;     // Set blink interval for LED 3 (1300 ms)

// Variables to store the current state of each LED
int LED1State = LOW; // Current state of LED 1 (LOW = off, HIGH = on)
int LED2State = LOW; // Current state of LED 2
int LED3State = LOW; // Current state of LED 3

void setup(){
  // The setup function runs once when the microcontroller starts
  // Initialize the LED pins and perform initial actions
  
  pinMode(LED_1_PIN, OUTPUT); // Set LED 1 pin as an output
  pinMode(LED_2_PIN, OUTPUT); // Set LED 2 pin as an output
  pinMode(LED_3_PIN, OUTPUT); // Set LED 3 pin as an output
         
  digitalWrite(LED_1_PIN, HIGH); // Turn on LED 1
  delay(1000);                   // Wait for 1 second
  digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED (on-board LED)
  delay(333);                    // Wait for 333 milliseconds
} 

void loop(){
  // The loop function runs continuously after setup()
  // It controls the blinking of each LED independently based on their intervals

  unsigned long timeNow = millis(); // Get the current time in milliseconds since the program started

  // --- LED 1 Blinking Control ---
  // Check if the time interval for LED 1 has passed
  if(timeNow - previousTimeLED1Blink > timeIntervalLED1Blink) {
    // Toggle the state of LED 1
    if (LED1State == LOW) {
      LED1State = HIGH;
    }
    else {
      LED1State = LOW;
    }
    digitalWrite(LED_1_PIN, LED1State);             // Update LED 1 with the new state (on/off)
    previousTimeLED1Blink += timeIntervalLED1Blink; // Update the last toggle time for LED 1
  }
  
  // --- LED 2 Blinking Control ---
  // Check if the time interval for LED 2 has passed
  if (timeNow - previousTimeLED2Blink > timeIntervalLED2Blink) {
    // Toggle the state of LED 2
    if (LED2State == LOW) {
      LED2State = HIGH;
    }
    else {
      LED2State = LOW;
    }
    digitalWrite(LED_2_PIN, LED2State);             // Update LED 2 with the new state (on/off)
    previousTimeLED2Blink += timeIntervalLED2Blink; // Update the last toggle time for LED 2
  }
  
  // --- LED 3 Blinking Control ---
  // Check if the time interval for LED 3 has passed
  if (timeNow - previousTimeLED3Blink > timeIntervalLED3Blink) {
    // Toggle the state of LED 3
    if (LED3State == LOW) {
      LED3State = HIGH;
    }
    else {
      LED3State = LOW;
    }
    digitalWrite(LED_3_PIN, LED3State);             // Update LED 3 with the new state (on/off)
    previousTimeLED3Blink += timeIntervalLED3Blink; // Update the last toggle time for LED 3
  }
}
