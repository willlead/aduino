#include <SPI.h>
#include <Ethernet.h>

byte MAC[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xEB};
IPAddress IP(192,168,2,4);
EthernetServer server(80);

void setup() {
 
 Ethernet.begin(MAC,IP);
 server.begin();
 Serial.begin(9600);
}

void loop() {
  EthernetClient client = server.available();  //서버 구축
  if(client) {//서버가 구축되면 true값으로 들어온다. 그때 수행됨.
    Serial.println("서버와 통신 시작");
    char c = client.read();//서버로부터 날라온 값을 읽는다.
    
    if(c='\n') { //통신 준비가 되면,
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
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
      client.println("<a href='http://www.kbs.co.kr'>한국방송</a>");
      client.println("</body>");
      
      client.println("</html>");      
    }
    delay(1);
    client.stop(); //클라이언트 중지
  }
}
