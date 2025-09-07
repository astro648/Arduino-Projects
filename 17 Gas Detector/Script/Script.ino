#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 6, 8, 9, 10, 11);

int redled = 2;
int greenled = 3;
int buzzer = 4;
int sensor = A0;
int sensorThresh = 200;

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  int analogValue = analogRead(sensor);
  Serial.println("Analog Value: ");
  Serial.println(analogValue);
  Serial.println("Sensor Thresh: ");
  Serial.println(sensorThresh);

  if (analogValue > sensorThresh) {
    Serial.println("Alert triggered"); 
    digitalWrite(greenled, LOW);
    digitalWrite(redled, HIGH);
    tone(buzzer, 1000, 10000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ALERT");
    delay(200);  
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("EVACUATE");
    delay(200);  
  } else {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SAFE");
    delay(200);  
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ALL CLEAR");
    delay(200);  
  }
}