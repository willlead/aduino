#include <SPI.h>
#include <Ethernet.h>
byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB};

//서버하려면 고정 IP를 사용해야함.
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);
String HTTP_req=""; //웹서버에 접속하면서 웹 브라우저가 웹서버로 처음 보내는 문자열
int led_pin = 9;
boolean LED_status = 0; // LED 상태 표시

void setup() {
  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  server.begin();
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  EthernetClient client = server.available(); // 이더넷 통신 시도
  if (client) {
//    Serial.println("서버와 통신 시작");
    boolean current = true;
    while (client.connected()) {
      if (client.available()) {        
        char c = client.read(); //서버에 들어온 값을 읽어 들인다.
        HTTP_req += c;

        if (c == '\n' && current) {
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
          client.println("<h1>LED 컨트롤</h1>");
          client.println("<p>LED 스위치(on/off)</p>");
          client.println("<form method='get'>");
          ProcessCheck(client);
          client.println("</form>");
          client.println("</body>");
          client.println("</html>");
          Serial.print(HTTP_req);
          HTTP_req = "";
//          delay(3000);
          break;
        }

        if(c == '\n') {
          current = true;
        } else if (c != '\r') {
          current = false;
        }

      }
    }
    delay(1);
    client.stop();
  }
}

void ProcessCheck(EthernetClient client){
  Serial.println("=======================");
  Serial.print("ProcessCheck: ");
  
  if(HTTP_req.indexOf("LED=1") > -1) {       
    if(LED_status) {
      LED_status = 0; 
    } else {
      LED_status = 1;
    }
    Serial.println(LED_status);
  }
  Serial.println("=======================");
  
  if(LED_status) {
    digitalWrite(led_pin, HIGH);
    //<input type=\"checkbox\" name=\"LED\" value =\"1\" checked onclick=\"submit();\"/> 전등
    client.println("<input type='checkbox' name='LED' value ='1' checked onclick='submit();'/> 전등");
  }else {
     digitalWrite(led_pin, LOW);
    //<input type=\"checkbox\" name=\"LED\" value =\"1\" onclick=\"submit();\"/> 전등
    client.println("<input type='checkbox' name='LED' value ='1' onclick='submit();'/> 전등");
  }
}
