#define US_TRIG_PIN 2 // Define the pin for the ultrasonic sensor trigger
#define US_ECHO_PIN 3 // Define the pin for the ultrasonic sensor echo
#define LED_RED 4 // Define the pin for the red LED
#define LED_YELLOW 5 // Define the pin for the yellow LED
#define LED_GREEN 6 // Define the pin for the green LED

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  pinMode(US_TRIG_PIN, OUTPUT); // Set the ultrasonic trigger pin as an output
  pinMode(US_ECHO_PIN, INPUT); // Set the ultrasonic echo pin as an input
  pinMode(LED_RED, OUTPUT); // Set the red LED pin as an output
  pinMode(LED_YELLOW, OUTPUT); // Set the yellow LED pin as an output
  pinMode(LED_GREEN, OUTPUT); // Set the green LED pin as an output
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(US_TRIG_PIN, LOW); // Set the trigger pin LOW to ensure a clean pulse
  delayMicroseconds(2); // Wait for 2 microseconds before sending the pulse
  digitalWrite(US_TRIG_PIN, HIGH); // Set the trigger pin HIGH to start the pulse
  delayMicroseconds(5); // Keep it HIGH for 5 microseconds to send the pulse
  digitalWrite(US_TRIG_PIN, LOW); // Set the trigger pin LOW to end the pulse

  // Calculate the duration and distance
  int duration = pulseIn(US_ECHO_PIN, HIGH); // Measure the duration of the pulse from the echo pin
  int distance = 0.0343 * duration / 2; // Calculate distance in centimeters (speed of sound is 0.0343 cm/µs)
  Serial.println(distance); // Print the measured distance to the serial monitor

  if (distance > 200) {
    // If the object is far, green light is ON, others are OFF
    digitalWrite(LED_GREEN, HIGH); // Turn on the green LED
    digitalWrite(LED_YELLOW, LOW); // Turn off the yellow LED
    digitalWrite(LED_RED, LOW); // Turn off the red LED
  } 
  else if (distance > 100 && distance <= 200) {
    // If object is midway, yellow light blinks
    digitalWrite(LED_GREEN, LOW); // Turn off the green LED
    digitalWrite(LED_RED, LOW); // Turn off the red LED
    digitalWrite(LED_YELLOW, HIGH); // Turn on the yellow LED
    delay(300); // Wait for 300 milliseconds to keep the yellow LED on
    digitalWrite(LED_YELLOW, LOW); // Turn off the yellow LED
    delay(300); // Wait for 300 milliseconds before blinking again
  } 
  else if (distance <= 100) {
    // If object is too close, red light blinks
    digitalWrite(LED_GREEN, LOW); // Turn off the green LED
    digitalWrite(LED_YELLOW, LOW); // Turn off the yellow LED
    digitalWrite(LED_RED, HIGH); // Turn on the red LED
    delay(300); // Wait for 300 milliseconds to keep the red LED on
    digitalWrite(LED_RED, LOW); // Turn off the red LED
    delay(300); // Wait for 300 milliseconds before blinking again
  }
}
