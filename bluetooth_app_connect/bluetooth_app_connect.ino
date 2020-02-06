//앱과 블루투스 연결

//블루투스 활용 헤더
#include <SoftwareSerial.h>

//bluetooth module Tx:Digital 2 Rx: Digital 3
SoftwareSerial BTSerial(2,3);


void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }

  if(Serial.available()){
    BTSerial.write(Serial.read());
  }

}
