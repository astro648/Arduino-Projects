#define US_TRIG_PIN 2
#define US_ECHO_PIN 3
#define LED_RED 4
#define LED_YELLOW 5
#define LED_GREEN 6

void setup() {
  Serial.begin(9600);
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(US_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(US_TRIG_PIN, LOW);

  // Calculate the duration and distance
  int duration = pulseIn(US_ECHO_PIN, HIGH);
  int distance = 0.0343 * duration / 2;
  Serial.println(distance);

  if (distance > 200) {
    // If the object is far, green light is ON, others are OFF
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } 
  else if (distance > 100 && distance <= 200) {
    // If object is midway, yellow light blinks
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    delay(300); // Adjust delay for blink speed
    digitalWrite(LED_YELLOW, LOW);
    delay(300);
  } 
  else if (distance <= 100) {
    // If object is too close, red light blinks
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    delay(300); // Adjust delay for blink speed
    digitalWrite(LED_RED, LOW);
    delay(300);
  }
}
