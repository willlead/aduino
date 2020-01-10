//목표: 조도센터로 led 켰다 끄기
//조건: 조도센서 (r: +), (l: 10k[R](l:-, r:a1))
int light;
int reg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // a1이 기준값 조도센서가 
  //9 led값
  //map 특정 범위 값을 다른 범위 값으로 변환
  //analogRead(A1) 기준값
  // 기준 최소값 0, 최대값 1023
  // 변환 최소값 0, 최대값 255
  reg = analogRead(A1);
  light = map(reg,400,910,0,255);  
  analogWrite(9,light);
  Serial.println(String("저항크기")+reg);
  Serial.println(String("빛의 밝기")+light);
  delay(200);
}
