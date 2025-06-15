#include <LiquidCrystal.h>
#include <math.h>

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
bool activateResults = false;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(buttons[i],INPUT);
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

void loop() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  for(int i = 0; i < 5; i++){
    state[i] = digitalRead(buttons[i]);
    if(state[i] == HIGH && i < 5){
      value[i]++;
      position = i * 4;
      lcd.setCursor(position, 1);
      lcd.print(value[i]);
    } else if (state[i] == HIGH && i == 4){
      activateResults();
    }
  }
}

void activateResults(){
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
