void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop()
{
  //int pValue = analogRead(A0) * 255 / 1023;
  int pValue = analogRead(A0) / 4;
  Serial.println(pValue);
  analogWrite(11,pValue);
}