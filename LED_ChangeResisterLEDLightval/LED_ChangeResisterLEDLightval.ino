//목표: 가변저항을 이용한 led 밝기 조절
// 조건 
const int POT = 0;
int ledPin = 5;
int val = 0;
int lightval;


void setup() {
  Serial.begin(9600);
  pinMode(POT, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  val = analogRead(POT);
  lightval = (val>>2);
  analogWrite(ledPin, lightval);
  Serial.println(String("저항값: ")+val+String(" 밝기 값: ")+lightval);
  delay(1000);

}
