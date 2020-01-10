#define RED 11
#define GREEN 10
#define BLUE 9
#define BUTTON 2

boolean lastButton = LOW; //이전 버튼 상태를 변수로 선언
boolean currentButton = LOW; //현재 버튼의 눌린 상태를 변수로 선언
//boolean ledOn = false; //현재 LED의 점멸 상태를 변수로 선언
int ledMode = 0;

void setup() { //초기화
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);
}


void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) { //버튼을 누름
    //ledOn = !ledOn; // led 점멸 상태를 바꿈
    ledMode++;
  }
  lastButton = currentButton; // 이전 버튼 값을 현재 버튼 값으로 변경
  //digitalWrite(LED, ledOn); //LED를 켜고 끄고 함.
  if(ledMode == 8) ledMode = 0;
  setMode(ledMode);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); //현재 버튼 상태를 확인
  if (last != current) { //이전 버튼 상태와 현재 버튼 상태가 다름
    delay(5); //5ms 기다린다.
    current = digitalRead(BUTTON);//현재 버튼 상태를 저장
  }
  return current;
}

void setMode(int mode) {
  if (mode == 1) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  } else if (mode == 2) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  } else if (mode == 3) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  } else if (mode == 4) {
    //보라색
    analogWrite(RED, 127);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 127);
  } else if (mode == 5) {
    //청록색
    analogWrite(RED, 0);
    analogWrite(GREEN, 127);
    analogWrite(BLUE, 127);
  } else if (mode == 6) {
    //오렌지색
    analogWrite(RED, 127);
    analogWrite(GREEN, 127);
    analogWrite(BLUE, 0);
  } else if (mode == 7) {
    //보라색
    analogWrite(RED, 85);
    analogWrite(GREEN, 85);
    analogWrite(BLUE, 85);
  } else {
    //꺼짐
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
}
