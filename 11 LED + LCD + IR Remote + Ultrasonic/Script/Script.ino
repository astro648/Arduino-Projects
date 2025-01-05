#include<LiquidCrystal.h>
#include<IRremote.h>

#define ir_receive_pin 5

#define echo_pin 3
#define trigger_pin 4

#define warning_led 11
#define error_led 12

#define lock_distance 10.0
#define warning_distance 50.0

#define lcd_rs_pin A5
#define lcd_e_pin A4
#define lcd_d4_pin 6
#define lcd_d5_pin 7
#define lcd_d6_pin 8
#define lcd_d7_pin 9

//IR button
//pl-5 off-0 eq-13 up-10 down-8
#define ir_button_play 64
#define ir_button_off 69
#define ir_button_eq 25
#define ir_button_up 9
#define ir_button_down 7

// lcd mode
#define lcd_distance_mode 0
#define lcd_settings_mode 1

//lcd
LiquidCrystal lcd(lcd_rs_pin,lcd_e_pin,lcd_d4_pin,
                  lcd_d5_pin,lcd_d6_pin,lcd_d7_pin);

//Calcualting time for ultraonic sensor trigger
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

//Calculating time for Wave Start and Wave returned
volatile unsigned long pulseInTimeBegin;
unsigned long pulseInTimeEnd;
bool newDistanceAvailable = false;

double prevDistance = 400.0;

//Warning LED
unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDDelay = 500;
byte warningLEDState = LOW;

//error led
unsigned long lastTimeErrorLEDBlinked = millis();
unsigned long errorLEDDelay = 300;
byte errorLEDState = LOW;

bool isLocked = false;

int lcdMode = lcd_distance_mode;

// Get the distance using ultrasonic sensor

void triggerUltrasonicSensor(){
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
}

double getUltrasonicDistance(){
  double durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  double distance = durationMicros / 58.0; //distance in cm
  if(distance > 400.0)
  {
    return prevDistance;
  }
  
  //distance = prevDistance * 0.6 + distance * 0.4;
  distance = prevDistance + 0.4 * (distance - prevDistance);
  prevDistance = distance;
  return distance;  
}

void echoPinInterrupt(){
  if(digitalRead(echo_pin) == HIGH){
    pulseInTimeBegin = micros();
  }else{ //stop the pulse
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}

void toggleErrorLED(){
  if(errorLEDState == LOW)
  {
    errorLEDState = HIGH;
  }
  else
  {
    errorLEDState = LOW;
  }
  digitalWrite(error_led, errorLEDState);
}

void toggleWarningLED()
{
  if(warningLEDState == LOW)
  {
    warningLEDState = HIGH;
  }
  else
  {
    warningLEDState = LOW;
  }
  digitalWrite(warning_led, warningLEDState);
}

void setWarningLEDBlinkRateFromDistance(double distance)
{
  // 0 to 400 cm -> 0 to 1600 ms
  warningLEDDelay = distance * 4;
  //Serial.print(distance);
  //Serial.print("---");
  //Serial.println(warningLEDDelay);
}

void lock(){
  if(!isLocked){
    isLocked = true;
    warningLEDState = LOW;
    errorLEDState = LOW;
  }
}

void unlock(){
  if(isLocked){
    isLocked = false;
    errorLEDState = LOW;
    digitalWrite(error_led, errorLEDState);
  }
}

void printDistanceOnLCD(double distance){
  if(isLocked){
    lcd.setCursor(0,0);
    lcd.print("!!! Obstacle !!!  ");
    lcd.setCursor(0,1);
    lcd.print("Press to unlock.  ");
    
  }else if(lcdMode == lcd_distance_mode){
    lcd.setCursor(0,0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm  ");
    
    lcd.setCursor(0,1);
    
    if(distance > warning_distance){
      lcd.print("no obstacle.   ");
    }else{
      lcd.print("!! Warning  !!");
    }
  }
}


void handleIRCommand(long command)
{
  switch(command)
  {
    case ir_button_play: {
      unlock();
      break;
    }
    case ir_button_off: {
    
      break;
    }
    case ir_button_eq: {
    
      break;
    }
    case ir_button_up: {
      toggleLCDScreen();
      break;
    }
    case ir_button_down: {
      toggleLCDScreen();
      break;
    }
    default: {
     //do nothing 
    }
  }
}

void toggleLCDScreen(){
  switch(lcdMode){
    case lcd_distance_mode: {
      lcdMode = lcd_settings_mode;
      break;
    }
    case lcd_settings_mode: {
      lcdMode = lcd_distance_mode;
      break;
    }
    default: {
      lcdMode = lcd_distance_mode;
    }
  }
  
  if(lcdMode == lcd_settings_mode){
    lcd.setCursor(0,0);
    lcd.print("Press on OFF to ");
    lcd.setCursor(0,1);
    lcd.print("reset settings.  ");
  }
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  IrReceiver.begin(ir_receive_pin);
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(warning_led, OUTPUT);
  pinMode(error_led, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(echo_pin),
                  echoPinInterrupt,
                  CHANGE);
  
  lcd.print("Initializing....");
  delay(3000);
  lcd.clear();
}

void loop() {
  unsigned long timeNow = millis();  
  
  if(isLocked){
    //blink error and warning leds at same time
    if(timeNow - lastTimeErrorLEDBlinked > errorLEDDelay)
    {
      lastTimeErrorLEDBlinked += errorLEDDelay;
      //blink LED
      toggleErrorLED();
      toggleWarningLED();
    }
  }else{
    if(timeNow - lastTimeWarningLEDBlinked > warningLEDDelay)
    {
      lastTimeWarningLEDBlinked += warningLEDDelay;
      //blink LED
      toggleWarningLED();
    }
  } 
  
  if(IrReceiver.decode()){
    IrReceiver.resume();
    long command = IrReceiver.decodedIRData.command;
    handleIRCommand(command);
    //Serial.println(command);
  }
  
  if(timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay)
  {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    //trigger ultrasonic sensor
    triggerUltrasonicSensor();
  }  
  
  if(newDistanceAvailable){
    newDistanceAvailable = false;
    double distance = getUltrasonicDistance();
    setWarningLEDBlinkRateFromDistance(distance);
    printDistanceOnLCD(distance);
    if(distance < lock_distance){
     lock(); 
    }
    //Serial.println(distance);
  }
}