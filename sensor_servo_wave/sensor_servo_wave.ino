//자동차 셔터 열고 닫기
// 초음파+서보모터

#include <Servo.h>
Servo myservo;
int pos = 0; //현재 각도
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
}

void loop() {
  for(pos =0; pos<180; pos++){
    myservo.write(pos);
    delay(15);
  }
}
