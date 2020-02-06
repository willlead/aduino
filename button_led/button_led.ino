#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

int LED_pin[] = {8, 9, 10};
int BUTTON_pin[] = {4, 5, 6};

boolean lastButton[] = {LOW, LOW, LOW}; //이전 버튼의 눌림 상태
boolean currentButton[] = {LOW, LOW, LOW}; //현재 버튼의 눌림 상태
boolean ledOn[] = {false, false, false}; //led점멸

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LED_pin[i], OUTPUT);
    pinMode(BUTTON_pin[i], INPUT);
  }
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    currentButton[i] = debounce(lastButton[i], i);
    if (lastButton[i] == LOW && currentButton[i] == HIGH) {
      ledOn[i] = !ledOn[i];
      char message[4] = "  \n"; //
      message[0] = i + 1 + '0'; //버튼번호
      message[1] = ledOn[i]+'0'; //켜진상태, 꺼진상태
      BTSerial.print(message);
      delay(200);
    }
    lastButton[i] = currentButton[i];
    digitalWrite(LED_pin[i], ledOn[i]);
  }
}

boolean debounce(boolean last, int i) {
  boolean current = digitalRead(BUTTON_pin[i]);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON_pin[i]);
  }
  return current;
}
