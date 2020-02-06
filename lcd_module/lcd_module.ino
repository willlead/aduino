#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);
  lcd.init(); // I2C LC를 초기화
  lcd.backlight(); //lcd 백라이트 켜줍니다.
  lcd.print("hello aduino !!! heellelelfleflel");

}

void loop() {
//  int value = random(0, 3);
//  Serial.println(value);
//  lcd.clear();
//  switch (value) {
//    case 0:
//      lcd.setCursor(0, 0);
//      lcd.print("hello");
//      break;
//    case 1:
//      lcd.setCursor(0, 1);
//      lcd.print("bye");
//      break;
//    case 2:
//      lcd.setCursor(0, 0);
//      lcd.print("hello");
//      lcd.setCursor(0, 1);
//      lcd.print("bye");
//      break;
//  }

while(true){
  lcd.scrollDisplayLeft();
  delay(500);
}
  delay(1000);
}
