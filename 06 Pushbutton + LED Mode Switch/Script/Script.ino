// This program controls three LEDs connected to digital pins 10, 11, and 12,
// and a pushbutton connected to digital pin 2.
// When the pushbutton is pressed, the LEDs toggle between two different patterns.

#define LED_1_PIN 12        // Define digital pin 12 for LED 1
#define LED_2_PIN 11        // Define digital pin 11 for LED 2
#define LED_3_PIN 10        // Define digital pin 10 for LED 3
#define PUSHBUTTON_PIN 2    // Define digital pin 2 for the pushbutton

#define LED_PIN_ARRAY_SIZE 3  // Size of the LED pin array

int LEDBlinkState = 1;      // Variable to keep track of the current LED state

// Array containing the LED pin numbers
byte LEDPinArray[LED_PIN_ARRAY_SIZE] = 
{LED_1_PIN, LED_2_PIN, LED_3_PIN};

// Function to set all LED pins as outputs
void setLEDPinModes()
{
  for(int i = 0; i < LED_PIN_ARRAY_SIZE; i++)
  {
    pinMode(LEDPinArray[i], OUTPUT);  // Set each LED pin as an output
  }
}

// Function to turn off all LEDs
void turnOffAllLEDs()
{
  for(int i = 0; i < LED_PIN_ARRAY_SIZE; i++)
  {
    digitalWrite(LEDPinArray[i], LOW);  // Set each LED pin to LOW (turn off)
  }
}

// Function to toggle LEDs between two patterns
void toggleLEDs()
{
  if(LEDBlinkState == 1){
      // Pattern 1: Turn on LED 1 and LED 3, turn off LED 2
      digitalWrite(LED_1_PIN, HIGH);
      digitalWrite(LED_2_PIN, LOW);
      digitalWrite(LED_3_PIN, HIGH);
      LEDBlinkState = 2;  // Update state to 2
    }
    else{
      // Pattern 2: Turn off LED 1 and LED 3, turn on LED 2
      digitalWrite(LED_1_PIN, LOW);
      digitalWrite(LED_2_PIN, HIGH);
      digitalWrite(LED_3_PIN, LOW);
      LEDBlinkState = 1;  // Update state to 1
    }
}

void setup()
{
  setLEDPinModes();     // Initialize LED pins as outputs
  turnOffAllLEDs();     // Turn off all LEDs at startup
}

void loop()
{
  // Check if the pushbutton is pressed (active LOW)
  if(digitalRead(PUSHBUTTON_PIN) == LOW){
    toggleLEDs();       // Toggle the LED patterns
    delay(300);         // Debounce delay or delay between toggles
  } 
}
