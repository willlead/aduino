#include <Servo.h>
Servo myservo;
int pos = 0; //현재 각도
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
}

void loop() {
  for(pos =0; pos<120; pos++){
    myservo.write(pos);
  }
}
