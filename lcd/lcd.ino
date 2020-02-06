#include <LiquidCrystal.h>
// lcd
//D4 2
//D5 3
//D6 4
//D7 5
//E  11
//RW GND
//RS 12
//V0 R(1k) GND
//VDD(VCC) +
//VSS(GND) GND

//조도(빛)센서
//한쪽은 +, 한쪽은 10k, 저항 왼쪽은 GND, 저항오른쪽은 A0

//초음파 센서
#define TRIG 9
#define ECHO 8

LiquidCrystal lcd(12, 11, 2, 3, 4, 5); //변수 초기화

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //16열 2행
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG, LOW);
  
  long distance = pulseIn(ECHO, HIGH) / 58.2;
  Serial.println(distance);
  lcd.clear();
  lcd.setCursor(0, 0);
  if (distance > 10) {
    
    lcd.print("safe");
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print(distance);
  } else {
    
    lcd.print("warnning");
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print(distance);
  }
  delay(200);

}
