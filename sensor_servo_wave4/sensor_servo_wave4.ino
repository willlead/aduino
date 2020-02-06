//자동차 차단기
include <Servo.h>
Servo myservo;
int pos = 0; //현재 각도
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
}

void loop() {
//  for(pos =0; pos<180; pos++){
//    myservo.write(pos);
//    delay(15);
//  }

myservo.write(map(analogRead(A0),0,1023,0,120));
delay(15);
}
