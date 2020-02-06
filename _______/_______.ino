#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
  //적외선 센서, 리모콘 16진수 값
  //0xFF02FD >>
  //0xFFC23D >
  //0xFFE01F -
  //0xFFA857 +
  //0xFF906F EQ
  //0xFF6897 0
  //0xFF9867 100+
  //0xFFB04F 200+
  //0xFF30CF 1
  //0xFF18E7 2
  //0xFF7A85 3
  //0xFF10EF 4
  //0xFF38C7 5
  //0xFF5AA5 6
  //0xFF42BD 7
  //0xFF4AB5 8
  //0xFF52AD 9
  
#define YELLOW 8
#define RED 9
#define GREEN 10

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {

  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //    irrecv.resume();
    switch (results.value) {
      case 0xFFA25D:
        Serial.println("CH-");
        LightControl(false, false, true);
        delay(500);
        LightControl(false, true, false);
        delay(500);
        LightControl(true, false, false);
        break;
      case 0xFFE21D:
        Serial.println("CH+");
        LightControl(true, false, false);
        delay(500);
        LightControl(false, true, false);
        delay(500);
        LightControl(false, false, true);
        break;
      case 0xFF629D:
        Serial.println("CH");
        LightControl(true, true, true);
        delay(500);
        LightControl(false, false, false);
        delay(500);
        LightControl(true, true, true);
        delay(500);
        LightControl(false, false, false);
        break;

      case 0xFF30CF:
        Serial.println("1");
        LightControl(true, false, false);
        break;
      case 0xFF18E7:
        Serial.println("2");
        LightControl(false, true, false);
        break;
      case 0xFF7A85:
        Serial.println("3");
        LightControl(false, false, true);
        break;
    }
    irrecv.resume();
    delay(1000);

  }
}

void LightControl(boolean y, boolean r, boolean g) {
  digitalWrite(YELLOW, y);
  digitalWrite(RED, r);
  digitalWrite(GREEN, g);
}
