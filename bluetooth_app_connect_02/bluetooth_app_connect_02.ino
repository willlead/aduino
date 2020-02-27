#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
byte buffer[1024];
int bufferPosition; //버퍼에 기록할 위치

//AT => OK
//AT+NAMEYOON 이름 설정
//AT+PIN1008 핀 설정


void setup() {
  Serial.begin(9600); //시리얼 모니터 초기화
  BTSerial.begin(9600); // 블루투스 모듈 초기화
  bufferPosition = 0;
}

void loop() {
  
  // 블루투스, 데이터 수신 가능 
  if(BTSerial.available()){ 
    byte data = BTSerial.read(); 
    Serial.write(data);

    //버퍼에 받은 데이터를 저장 후 bufPos를 증가시킨다.
    buffer[bufferPosition++] = data;    
    
    // 데이터 끝을 만나면
    if(data == '\n'){ 
      buffer[bufferPosition] = '\0';

      //스마트폰으로 전송할 문자를 시리얼 모니터에 출력
      Serial.print("보내는 문자: ");      
      Serial.write(buffer, bufferPosition);
      BTSerial.write(buffer, bufferPosition);
      bufferPosition = 0;
      
    }
  }
}
