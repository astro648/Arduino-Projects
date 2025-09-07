#include <LiquidCrystal.h>
#include <math.h>

#define sw1 A0

const int buttons[5] = {A0,A1,A2,A3,7};

int state[5] = {0, 0, 0, 0, 0};
int value[5] = {0, 0, 0, 0, 0};
int position, winner, winnerCount;

#define LCD_RS 13
#define LCD_E 12
#define LCD_DB4 11
#define LCD_DB5 10
#define LCD_DB6 9
#define LCD_DB7 8

#define PIEZO 4
#define LED_GREEN 5
#define LED_RED 6

int countA = 0, countB = 0, countC = 0, countD = 0;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(buttons[i],INPUT_PULLUP);
  }
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIEZO, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("A   B   C   D   ");
  lcd.setCursor(0,1);
  lcd.print("0   0   0   0   ");
}

bool buttonPressed = false;
void loop() {
  //digitalWrite(LED_RED, LOW);
  //digitalWrite(LED_GREEN, LOW);
  //Serial.println("Loop begin");
  //for(int i = 0; i < 5; i++){
    //state[i] = digitalRead(buttons[i]);    
    //Serial.print("state = ");
    //Serial.print(i);
    //Serial.print(" = ");
    //Serial.println(state[i]);
    //delay(1000);
    //if(state[i] == 0){
      //Serial.println("Vote received");
      //value[i]++;
      //position = i * 4;
      //lcd.setCursor(position, 1);
      //lcd.print(value[i]);
      //Serial.print("value = ");
      //Serial.println(value[i]);
      //delay(5000);
    //} else if (state[i] == 0 && i == 4){
      //Serial.println("Activate results button clicked");
      //activateResults();
    //}
  //}
  int sw = buttons[0];
  if (digitalRead(sw) == 0 && !buttonPressed) {
    Serial.println("0");
    value[0]++;
    Serial.println("switch 1 pressed");
    buttonPressed = true; // mark as pressed
  }

  if (digitalRead(sw) == 1) {
    buttonPressed = false; // reset when button released
  }
  
}

void activateResults(){
  Serial.println("Activate results");
  lcd.clear();
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(PIEZO, HIGH);

  int maxVal = 0;
  winnerCount = 1;
  for (int i = 0; i < 4; i++){
    if(value[i] > maxVal){
      maxVal = value[i];
      winner = i;
    }
  }
  for (int i = 0; i < 4; i++){
    if(value[i] == maxVal && i > winner){
      winnerCount++;
    }
  }

  delay(1000);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(PIEZO, LOW);
  
  if(winnerCount == 1){
    lcd.print("Winner is candidate ");
    lcd.print((char)('A'+winner));
  } else if (winnerCount > 1){
    lcd.print("There is a tie.");
  }
}
