#define LED 9
#define BUTTON 2

boolean lastButton = LOW; //이전 버튼 상태를 변수로 선언
boolean currentButton = LOW; //현재 버튼의 눌린 상태를 변수로 선언
boolean ledOn = false; //현재 LED의 점멸 상태를 변수로 선언

void setup() { //초기화
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

//데이터 처리
void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) { //버튼을 누름
    ledOn = !ledOn; // led 점멸 상태를 바꿈
  }
  lastButton = currentButton; // 이전 버튼 값을 현재 버튼 값으로 변경
  digitalWrite(LED, ledOn); //LED를 켜고 끄고 함.
}


boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); //현재 버튼 상태를 확인
  if (last != current) { //이전 버튼 상태와 현재 버튼 상태가 다름
    delay(5); //5ms 기다린다.
    current = digitalRead(BUTTON);//현재 버튼 상태를 저장
  }
  return current;
}

//스위치 바운싱(채터링 또는 진동 잡읍)
//1. 버튼의 기계적인 현상
//2. 값이 변경되는 것을 알아내기 어렵다.
//3. 실제로 버튼을 눌러도 예상대로 작동하지 않는 경우가 많다.

//1. 이전 버튼 상태와 현재 버튼 상태를 저장
//2. 현재 버튼 상태를 읽어 온다.
//3. 입력 값이 이전 버튼 상태와 다를 때는 바운싱이 끝날때까지 5ms동안 기다린다.
//4. 5ms 후에 버튼 상태를 다시 읽어서 그 값을 현재 버튼 상태로 저장한다.
//5. 이전 상태가 LOW이고 현재 버튼 상태가 HIGH라면 LED 상태를 전환한다.
//6.
