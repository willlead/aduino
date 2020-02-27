#include <SD.h>

#include <SPI.h>
#include <Ethernet.h>

byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB}; //mac 고유 번호
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);

File webFile;// index.html 파일을 이용하기에 file 변수가 필요하다.

void setup() {
  Serial.begin(9600);
  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  server.begin();
  Serial.println("sd카드 초기화");
  if(!SD.begin(4)) { // 포트번호 4로 고정되어있음.
    Serial.println("에러 - sd카드 초기화 실패");  
  } else {
    Serial.println("성공 - sd카드 초기화");  
  }
  
  if(!SD.exists("index.htm")){ //파일 존재 하는지
    Serial.println("index.html 찾을 수 없습니다.");
  } else {
    Serial.println("index.html 파일을 찾았습니다.");  
  }
}

void loop() {
  EthernetClient client = server.available();
  if(client){
    boolean current = true;
    while(client.connected()){ // 클라이언트가 연결 상태이면
      if(client.available()){ // 다시 클라이언트는 사용가능한 상태여야 한다.
        char c = client.read(); // 1byte 씩 읽는다.
        if(current){ // 한줄 다 받으면 \n이 나온다.
           client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          // html 파일 읽어서 이더넷에 적용한다.
          webFile = SD.open("index.htm");
          if(webFile){
            while(webFile.available()){
              client.write(webFile.read());
            }
            webFile.close();
          }

          if(c != '\r'){
            current = false;
          }
          delay(1);
          client.stop();
        }
      }
    }
  }

}
