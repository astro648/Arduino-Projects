// This program reads an analog input from pin A0 (such as a potentiometer),
// scales the value to a range suitable for PWM output, and writes it to digital pin 11.
// It also prints the scaled value to the serial monitor for debugging or monitoring purposes.

void setup()
{
  Serial.begin(9600);    // Initialize serial communication at 9600 bits per second
  pinMode(11, OUTPUT);   // Set digital pin 11 as an output for PWM signal
}

void loop()
{
  // Read the analog input from pin A0 (range 0 to 1023)
  // Scale it down to 0 to 255 for PWM output
  // int pValue = analogRead(A0) * 255 / 1023; // Alternative scaling method
  int pValue = analogRead(A0) / 4; // Divide by 4 to scale 0-1023 to 0-255

  Serial.println(pValue);          // Print the scaled value to the serial monitor
  analogWrite(11, pValue);         // Write the PWM signal to pin 11
}
