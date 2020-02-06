#include <SoftwareSerial.h>

//bluetooth module Tx:Digital 2 Rx: Digital 3
SoftwareSerial BTSerial(2, 3);

int pin_red = 9;
int pin_green = 10;
int pin_blue = 11;

String buffer = "";
void setup() {

  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);

}

void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    if(data == '\n') {
      Serial.println(buffer);
      if(buffer.length() > 1) {
        int b = buffer.substring(1).toInt();
        switch(buffer[0]) {
          case 'R':
          analogWrite(pin_red, b);
          break;
          case 'G':
          analogWrite(pin_green, b);
          break;
          case 'B':
          analogWrite(pin_blue, b);
          break;
        }
      }
      buffer = "";
    } else {
      buffer += data;
    }
    
  }
  
//  if (BTSerial.available()) {
//    Serial.write(BTSerial.read());
//  }
}
