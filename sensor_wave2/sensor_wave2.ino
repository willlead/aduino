// 초음파 센서로 거리 측정

#define TRIG 3
#define ECHO 2
#define RED 11
#define GREEN 10
#define BLUE 9

int volumn; 
int led = 9;
int threshold = 540;
int pin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
}

void loop() {

  volumn = analogRead(A0);
  Serial.println(volumn, DEC);
  delay(100);
  if(volumn >= threshold){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG, LOW);
  //echo 핀에 초음파가 들어오는 시간을 계산
  //(반환된 값을 58.2로 나눈 이유는 시간을 cm로 변경하는 공식)
  long distance = pulseIn(ECHO, HIGH)/58.2;
  Serial.println(distance);
  analogWrite(RED,0);
  analogWrite(GREEN,0);
  analogWrite(BLUE,0);
  if(distance < 10){
    analogWrite(RED,255);
  } else if(distance <20) {
    analogWrite(GREEN,255);
  } else if(distance <30){
    analogWrite(BLUE,255);
  }
  delay(100);
}
