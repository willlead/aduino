#define LED 9
#define BUTTON 2

boolean ledOn = false; //현재 LED의 점멸 상태를 변수로 선언

void setup() { //초기화
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

//데이터 처리
void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    ledOn = !ledOn;
    digitalWrite(LED, ledOn);
  }
}

