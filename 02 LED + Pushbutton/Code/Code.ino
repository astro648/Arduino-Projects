#define LED_1_PIN 9
#define PUSHBUTTON_PIN 2
void setup()
{
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(PUSHBUTTON_PIN, INPUT);
}

void loop()
{
  if(digitalRead(PUSHBUTTON_PIN) == HIGH){
    digitalWrite(LED_1_PIN, HIGH);
  } else {
    digitalWrite(LED_1_PIN, LOW);
  }
}