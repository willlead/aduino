void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(8, map(analogRead(A0),0,1023,31,4978),20);
  
  delay(500);
}
