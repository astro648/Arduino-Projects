// Libraries
#include <IRremote.h>         // Include the IR remote library for infrared communication
#include <LiquidCrystal.h>    // Include the LiquidCrystal library for controlling the LCD

// Pin Definitions
#define LED_RED 8             // Pin 8 connected to the red LED
#define LED_YELLOW 2          // Pin 2 connected to the yellow LED
#define LED_GREEN 3           // Pin 3 connected to the green LED
#define LCD_E A5              // Pin A5 connected to LCD's Enable pin
#define LCD_RS A4             // Pin A4 connected to LCD's Register Select pin
#define LCD_DB4 4             // Pin 4 connected to LCD's data pin 4
#define LCD_DB5 5             // Pin 5 connected to LCD's data pin 5
#define LCD_DB6 6             // Pin 6 connected to LCD's data pin 6
#define LCD_DB7 7             // Pin 7 connected to LCD's data pin 7
#define IRRECV 10             // Pin 10 connected to the IR receiver

// IR Remote Button Definitions
#define IRREMOTE_0 12         // IR code for button '0'
#define IRREMOTE_1 16         // IR code for button '1'
#define IRREMOTE_2 17         // IR code for button '2'
#define IRREMOTE_3 18         // IR code for button '3'

// Initialize the LCD with the specified pins
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup(){
  Serial.begin(9600);             // Initialize serial communication at 9600 baud
  IrReceiver.begin(IRRECV);       // Start the IR receiver on the specified pin
  lcd.begin(16,2);                // Initialize the LCD with 16 columns and 2 rows
  
  // Set pin modes for LEDs
  pinMode(LED_RED, OUTPUT);       // Set the red LED pin as an output
  pinMode(LED_YELLOW, OUTPUT);    // Set the yellow LED pin as an output
  pinMode(LED_GREEN, OUTPUT);     // Set the green LED pin as an output

  // Turn off all LEDs initially
  digitalWrite(LED_RED, LOW);     // Ensure the red LED is off
  digitalWrite(LED_YELLOW, LOW);  // Ensure the yellow LED is off
  digitalWrite(LED_GREEN, LOW);   // Ensure the green LED is off
}

void loop(){
  int command = -1;               // Initialize the command variable
  if (IrReceiver.decode()) {      // Check if an IR signal has been received
    command = IrReceiver.decodedIRData.command;  // Store the received IR command
    Serial.println(command);      // Print the command to the serial monitor
  }
  if (command == IRREMOTE_0) {    // If the '0' button was pressed
    Serial.println("Toggle LEDs"); // Print action to the serial monitor
    lcd.clear();                  // Clear the LCD display
    lcd.print("Toggle LEDs");     // Display "Toggle LEDs" on the LCD
    // Toggle the red LED
    if (digitalRead(LED_RED) == HIGH){
      digitalWrite(LED_RED, LOW);
    }else{
      digitalWrite(LED_RED, HIGH);
    }
    // Toggle the yellow LED
    if (digitalRead(LED_YELLOW) == HIGH){
      digitalWrite(LED_YELLOW, LOW);
    }else{
      digitalWrite(LED_YELLOW, HIGH);
    }
    // Toggle the green LED
    if (digitalRead(LED_GREEN) == HIGH){
      digitalWrite(LED_GREEN, LOW);
    }else{
      digitalWrite(LED_GREEN, HIGH);
    }
  }
  if (command == IRREMOTE_1){     // If the '1' button was pressed
    Serial.println("Red LED Blink"); // Print action to the serial monitor
    lcd.clear();                  // Clear the LCD display
    lcd.print("Red LED Blink");   // Display "Red LED Blink" on the LCD
    // Blink the red LED
    if(digitalRead(LED_RED) == HIGH){
      digitalWrite(LED_RED, LOW);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_RED, HIGH);
    } else if(digitalRead(LED_RED) == LOW){
      digitalWrite(LED_RED, HIGH);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_RED, LOW);
    }
  } else if (command == IRREMOTE_2){ // If the '2' button was pressed
    Serial.println("Yellow LED Blink"); // Print action to the serial monitor
    lcd.clear();                  // Clear the LCD display
    lcd.print("Yellow LED Blink");// Display "Yellow LED Blink" on the LCD
    // Blink the yellow LED
    if(digitalRead(LED_YELLOW) == HIGH){
      digitalWrite(LED_YELLOW, LOW);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_YELLOW, HIGH);
    } else if(digitalRead(LED_YELLOW) == LOW){
      digitalWrite(LED_YELLOW, HIGH);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_YELLOW, LOW);
    }
  } else if (command == IRREMOTE_3){ // If the '3' button was pressed
    Serial.println("Green LED Blink"); // Print action to the serial monitor
    lcd.clear();                  // Clear the LCD display
    lcd.print("Green LED Blink"); // Display "Green LED Blink" on the LCD
    // Blink the green LED
    if(digitalRead(LED_GREEN) == HIGH){
      digitalWrite(LED_GREEN, LOW);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_GREEN, HIGH);
    } else if(digitalRead(LED_GREEN) == LOW){
      digitalWrite(LED_GREEN, HIGH);
      delay(200);                 // Wait for 200 milliseconds
      digitalWrite(LED_GREEN, LOW);
    }
  }
  IrReceiver.resume();            // Prepare to receive the next IR signal
}
