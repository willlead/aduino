// 7세그먼트 연결방법
//12 2  
//9  3 
//8  4 
//6  5
//11 a r 6
//7 b r 7
//4 c r 8
//2 d r 9
//1 e r 10
//10 f r 11
//5 g r 12
//3 dp r 13

//0~9까지의 숫자 표현
byte pattern[] = { 
   0xFC, // 1111 1100 숫자 0
   0x60, // 0110 0000 숫자 1
   0xDA, // 숫자 2
   0xF2, // 숫자 3
   0x66, // 숫자 4
   0xB6, // 숫자 5
   0xBE, // 숫자 6
   0xE4, // 숫자 7
   0xFE, // 숫자 8
   0xE6  // 숫자 9
   };
   
int digit_select_pin[] = {2,3,4,5}; //자리수 선택 핀
// 7세그먼틑 모듈 연결 핀 a,b,c,d,e,f,g,dp 순서 
int segment_pin[] = {6,7,8,9,10,11,12,13};

unsigned long time_previous, time_current;
int minutes = 0, seconds = 0;

void setup() {
  Serial.begin(9600);
  for(int i =0; i<4; i++){ //자리수 선택 핀 출력으로 설정
    pinMode(digit_select_pin[i],OUTPUT);
  }

  for(int i =0; i<8; i++){ //세그먼트 제어 핀 출력으로 설정
    pinMode(segment_pin[i],OUTPUT);    
  }  
  time_previous = millis();
}

void loop() {
  int reading = analogRead(A0); //가변저항 값을 읽어서 변수에 저장
  //Serial.println(reading);
  show_4_digit(reading);

//  time_current = millis();
//  
//  //1초 경과
//  if(time_current - time_previous >= 1000) {
//    time_previous = time_current;
//    seconds++; // 1초 증가
//
//    // 60초가 되면 분 증가
//    if(seconds == 60) {
//      seconds = 0;
//      minutes++;
//    }
//    
//    // 60분이 되면 0으로 되돌림
//    if(minutes == 60) minutes = 0;        
//  }
//  //시간 표시를 위해 4자리 숫자로 만듦 
//  show_4_digit(minutes * 100 + seconds); 
}

//해당 자리에 숫자 하나를 표시하는 함수
void show_digit(int pos, int number){ //위치, 수수자
  for(int i = 0; i<4; i++){
    if(i+1 == pos) {
      digitalWrite(digit_select_pin[i], HIGH);
    } else {
      digitalWrite(digit_select_pin[i], LOW);
    }
  }

  for(int i=0; i<8; i++){
    boolean on_off = bitRead(pattern[number], 7-i);
    Serial.print(on_off);
    digitalWrite(segment_pin[i], !on_off);
  }
  Serial.println();
}

//4자리 7세그먼트 표시 장치에 4자리 숫자를 표시하는 함수
void show_4_digit(int number4){
  int number = number4;
  number = number %10000; // 4자리 제한 

  //천의 자리
  int thousands = number /1000; 
  number = number%1000;

  //백의 자리
  int hundreads = number / 100;
  number = number%100;

  //십의 자리
  int tens = number/10; 
  //일의 자리
  int ones = number % 10;
  
  if(number4 > 999) 
    show_digit(1, thousands);
  delay(5);
  if(number4 > 99) 
    show_digit(2, hundreads);
  delay(5);
  if(number4 > 9) 
    show_digit(3, tens);
  delay(5);
  show_digit(4, ones);
  delay(5);
}
