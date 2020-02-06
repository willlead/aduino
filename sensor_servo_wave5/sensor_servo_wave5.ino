//자동차 차단기
#define TRIG 3
#define ECHO 2

#define RED 5
#define GREEN 6

#include <Servo.h>
Servo myservo;

int pos = 0; //현재 각도
void setup() {
  Serial.begin(9600);

  myservo.attach(9);
  myservo.write(pos);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG, LOW);

  //echo 핀에 초음파가 들어오는 시간을 계산
  //(반환된 값을 58.2로 나눈 이유는 시간을 cm로 변경하는 공식)
  long distance = pulseIn(ECHO, HIGH) / 58.2;
  Serial.println(distance);

  if (distance > 30) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    
    delay(2000);
    if (pos != 0) {
      for (pos = 90; pos > 0; pos--) {
        myservo.write(pos);
        delay(15);
      }
    }
  } else {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    if (pos != 90) {
      for (pos = 90; pos >= 90; pos--) {
        myservo.write(pos);
        delay(15);
      }
    }
  }
  delay(100);
}
