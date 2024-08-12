#define LED_1_PIN 11
#define LED_2_PIN 10
#define LED_3_PIN 9
#define PUSHBUTTON_PIN 2

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(PUSHBUTTON_PIN, INPUT);
}

void loop()
{
  for(int i = 1; i <= 3; i = i){
  	if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 1){
      	digitalWrite(LED_3_PIN, LOW);
    	digitalWrite(LED_1_PIN, HIGH);
        delay(100);
        i++;
    } else if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 2){
    	digitalWrite(LED_2_PIN, HIGH);
      	digitalWrite(LED_1_PIN, LOW);
        delay(100);
        i++;
    } else if(digitalRead(PUSHBUTTON_PIN) == HIGH && i == 3){
    	digitalWrite(LED_3_PIN, HIGH);
      	digitalWrite(LED_2_PIN, LOW);
        delay(100);
        i++;
    }
  }
}