int led = 13;

void setup() {
  //pinMode: 각 핀의 입출력
  pinMode(led, OUTPUT);

}

void loop() {
  // digital : 출력 핀의 상태를 지정할 때 사용
  digitalWrite(led, HIGH); //ON
  delay(1000); // 1초 후
  digitalWrite(led, LOW); //OFF
  delay(1000); // 1초 후  
}
