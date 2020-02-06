#include <SoftwareSerial.h>

//bluetooth module Tx:Digital 2 Rx: Digital 3
SoftwareSerial BTSerial(2, 3);

int pin = A0;
int value_previous, value_current;

String buffer = "";
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  value_previous = analogRead(pin);
  sendData(value_previous);
}

void loop() {
  value_current = analogRead(pin);

  if (value_current != value_previous) {
    value_previous = value_current;
    sendData(value_current);
  }
  delay(1000);
}

void sendData(int value) {
  Serial.println(String("가변 저항값= ") + value_current);
  Serial.println(String("전압= ") + (value_current * 5 / 1023.0) + String("V"));

  String message = String(value) + '\n';
  BTSerial.print(message);
}
