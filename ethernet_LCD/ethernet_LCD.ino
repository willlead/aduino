#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD I2 줏 확인(모듈);

byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB}; //mac 고유 번호
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);

String request = ""; // lcd 전달하는 값을 초기화

void setup() {
  Serial.begin(9600);
  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  server.begin();

  lcd.init();
  lcd.backlight(); //lcd 백라이트 켜줍니다.
}

void loop() {

  EthernetClient client = server.available(); // 이더넷 통신 시도
  if (client) { //웹브라우저가 홈페이지에 접속한 경우(예: 192.168.2.75
    while (client.connected()) {
      if (client.available()) {
        char c  = client.read();
        request += c;

        if (c == '\n') {
          // HTML 문서 헤더
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          //클라이언트 홈페이지 주소를 입력하면 브라우저 화면에 뿌려줄 내용
          client.println("<!DOCTYPE html>");
          client.println("<html>");

          client.println("<head>");
          client.println("<meta charset = 'utf-8'/>");
          client.println("<title>IOT 홈페이지</title>");
          client.println("</head>");

          client.println("<body>");

          client.println("<h1>성렬이의 IOT 홈페이지에 오신 것을 환영합니다.</h1>");
          client.println("<p>회사 옥외 광고 내용 변경하기</p>");

          client.println("<form method='get'>");
          client.println("<p>옥외 광고 윗줄 (최대 16자) 내용</p>");
          client.println("<input type = 'text' name = 'val1'/>");
          client.println("<p>옥외 광고 아랫줄 (최대 16자) 내용</p>");
          client.println("<input type = 'text' name = 'val2'/>");
          client.println("</br>");
          client.println("<input type = 'submit' value='전송'/>");
          client.println("</form>");
          client.println("</body>");
          client.println("</html>");
          client.println();
          delay(1);
          client.stop();//홈페이지 html 작성 완료

          Serial.println("시작");
          Serial.println(request);
          String req_back = request;
          if (request.indexOf("val1")>=0 && request.indexOf("val2")>=0) {
          lcd.clear();
            request.remove(0, 11);
            Serial.print("첫번째 문구: ");
            Serial.println(request);
            for (int t = 16; t >= 0; t--) {
              request.remove(t);
              if (request.lastIndexOf("&") == -1) {
                break;
              }
            }
            Serial.print("첫번째 문구: ");
            Serial.println(request); //첫번째줄 문자열만 남아있을 것이다.
            lcd.setCursor(0, 0);
            lcd.print(request); //첫번째 문자 출력 완료

            // 텍스트 복원 후 두번째 문자열 찾기 시작
            request = req_back;
            request.remove(0, 11); //앞 13자리 지우기

            int temp = 0;
            int count = 0;
            while (true) {
              request.remove(0, temp);
              Serial.println(request);

              if (request.startsWith("&val2")) {
                Serial.println("두번째 줄 문자 시작!!");
                Serial.println(request);
                req_back = request;

                for (int i = 14; i < 32; i++) {
                  request.remove(i);
                  Serial.print("현재값: ");
                  Serial.println(request);
                  
                  //선생님 코드
//                  if (request.lastIndexOf("HTTP/1.1") != -1) {
//                    request.remove(i- 8); //http/1.1 가 8글자이므로 뺀다.
//                    break;
//                  }

                  //내생각으로 인덱스 찾아서 지우기
                  if (request.indexOf("HTTP/1.1") != -1) {
                    int index = request.indexOf("HTTP/1.1");
                    request.remove(index, request.length());
                    break;
                  }                  
                  request = req_back;
                }
                
                request.remove(0, 6);// "&val2=" 지우기
                Serial.print("두번째 출력 내용: ");
                Serial.println(request);
                lcd.setCursor(0, 1);
                lcd.print(request);
                break;
              }
              temp = 1;
              count++;
              if (request.length() == 0) {
                lcd.setCursor(0, 0);
                lcd.print("");
                break;
              }
            }
          }
          request = "";
        }
      }
    }
  }
}
