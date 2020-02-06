int reading;
int lmPin  = A0;
float temper;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() {
  reading = analogRead(lmPin);
  temper = reading/9.31;
  Serial.println(temper);
  delay(1000);

}
