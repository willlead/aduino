const int POT = 0; //아날로그 입력 a0핀을 사용함.
int led_pin[]={2,3,4,5};
int val = 0; //가변저항값으 저장하는 변수
int count; //LED 개수 결정

void setup() {
  Serial.begin(9600);
  pinMode(POT,INPUT);
  for(int i =0; i<4; i++){
    pinMode(led_pin[i],OUTPUT);
  }
}

void loop() {
  val = analogRead(POT); //가변 저항 값 읽기
  count = (val >> 8)+1; //
  for(int i=0; i<4; i++){
    if(i<count){
      if(val==0){
        digitalWrite(led_pin[i], LOW);  
      } else {
        digitalWrite(led_pin[i], HIGH);  
      }      
    } else {
      digitalWrite(led_pin[i], LOW);
    }
    
  }
  Serial.println(String("저항값: ")+val+String(" LED개수: ")+count);
  
  delay(1000);
}
