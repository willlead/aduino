#include <SPI.h>
#include <Ethernet.h>
byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB};

//서버하려면 고정 IP를 사용해야함.
IPAddress IP(192, 168, 2, 4);
EthernetServer server(80);

void setup() {
  Ethernet.begin(MAC, IP);
  server.begin();
  Serial.begin(9600);
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("서버와 통신 시작");
    boolean current = true;
    while (client.available()) {
      if (client.available()) {
        //서버에 들어온 값을 읽어 들인다.
        char c = client.read();
        if (current) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          
          // 웹페이지를 3초마다 갱신
          client.println("Refresh:3"); 
          client.println();

          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<meta charset = 'utf-8'/>");
          client.println("<title>아두이노 웹서버</title>");
          client.println("</head>");

          client.println("<body>");
          client.println("<h1>우리집에 오신 것을 환영합니다.</h1>");
          client.println("<p>여러가지 제품의 상태 및 컨트롤 </p>");
          client.println("<span>가변 저항 값: </span>");
          client.println(analogRead(A0));//아날로그 값을 
          Serial.println(analogRead(A0));
          client.println("<p>============</p>");
          client.println("<a href='http://www.naver.co.kr'>한국방송</a>");
          client.println("</body>");
          client.println("</html>");

          if (c != '\r') {
            current = false;
          }
        }
      }
    }
    delay(1);
    client.stop();
  }
}
