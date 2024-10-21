#include <LiquidCrystal.h> // Include the library for controlling the LCD display

// Define the pins connected to the LCD
#define LCD_RS_PIN A5  // Register Select pin
#define LCD_E_PIN A4   // Enable pin
#define LCD_D4_PIN 6   // Data pin 4
#define LCD_D5_PIN 7   // Data pin 5
#define LCD_D6_PIN 8   // Data pin 6
#define LCD_D7_PIN 9   // Data pin 7

// Initialize the LiquidCrystal object with the specified pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// Define the pins used for the ultrasonic sensor
const int trigPin = 4;  // Trigger pin for the ultrasonic sensor
const int echoPin = 3;  // Echo pin for the ultrasonic sensor

long duration;    // Variable to store the duration of the ultrasonic pulse
String distance;  // Variable to store the calculated distance

int cursorLine = 0; // Variable to keep track of the current line on the LCD

// Function to print user text on the LCD display
void printUserTextOnDisplay(String text) {
  // Validate the text length to fit on the LCD (maximum 16 characters)
  if (text.length() > 16) {
    text = "Text too long";
  }
  // Pad the text with spaces to clear the line on the LCD
  for (int i = text.length(); i < 16; i++) {
    text += " ";
  }
  // Set the cursor to the appropriate line (0 or 1)
  lcd.setCursor(0, cursorLine);
  // Print the text on the LCD
  lcd.print(text);
}

void setup() {
  Serial.setTimeout(10);         // Set the timeout for the serial input
  lcd.begin(16, 2);              // Initialize the LCD with 16 columns and 2 rows
  pinMode(trigPin, OUTPUT);      // Set the trigger pin as an output
  pinMode(echoPin, INPUT);       // Set the echo pin as an input
  Serial.begin(9600);            // Initialize serial communication at 9600 baud rate
}

void loop() {
  // Generate a trigger pulse to initiate a measurement
  digitalWrite(trigPin, LOW);    // Ensure the trigger pin is low for 2 microseconds
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);   // Set the trigger pin high for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);    // Set the trigger pin back to low

  // Measure the pulse duration on the echo pin
  duration = pulseIn(echoPin, HIGH); // Get the duration of the echo pulse

  // Calculate the distance using the speed of sound (0.034 cm/Âµs) divided by 2
  distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  // Display the distance on the LCD
  printUserTextOnDisplay(distance);
}