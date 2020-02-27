#include <SPI.h>
#include <Ethernet.h>

byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB};
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);

#define RED  4
#define GREEN  5
#define YELLOW  6

void setup() {
  Serial.begin(9600);
  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  server.begin();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

void loop() {
  EthernetClient client = server.available(); // 이더넷 통신 시도
  if (client) {
//    Serial.println("서버와 통신 시작");
    boolean current = true;
    String buffer = ""; //버퍼 초기화
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); //서버에 들어온 값을 읽어 들인다.        
        buffer += c;
        if (c == '\n') {
          Serial.print(c);
          buffer = "";
          delay(1000);
        } else if (c == '\r') {
          Serial.println(c);
          if (buffer.indexOf("GET /led.cgi?led_status=1") >= 0) {
            digitalWrite(RED, HIGH);
            digitalWrite(GREEN, LOW);
            digitalWrite(YELLOW, LOW);
            status_check(client);
          } else if (buffer.indexOf("GET /led.cgi?led_status=2") >= 0) {
            digitalWrite(RED, LOW);
            digitalWrite(GREEN, HIGH);
            digitalWrite(YELLOW, LOW);
            status_check(client);
          } else if (buffer.indexOf("GET /led.cgi?led_status=3") >= 0) {
            digitalWrite(RED, LOW);
            digitalWrite(GREEN, LOW);
            digitalWrite(YELLOW, HIGH);
            status_check(client);
          } else {
            digitalWrite(RED, LOW);
            digitalWrite(GREEN, LOW);
            digitalWrite(YELLOW, LOW);
            status_check(client);
          }
        }
      }
    }
  }
}

void status_check(EthernetClient client) {
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
  
  if(digitalRead(RED) > 0) {
    client.println("RGB LED가 현재<font color = 'red'>RED</font>상태입니다. ");
  } else if(digitalRead(GREEN) > 0) {
    client.println("RGB LED가 현재<font color = 'green'>GREEN</font>상태입니다. ");
  } else if(digitalRead(YELLOW) > 0) {
    client.println("RGB LED가 현재<font color = 'blue'>BLUE</font>상태입니다. ");
  } else {
     client.println("RGB LED가 현재<font color = 'black'>OFF</font>상태입니다. ");
  }
  client.println("<br/>");
  
  client.println("<form method='get' action ='/led.cgi'>");
  radiohtml(client);
  client.println("<input type='submit' value='전송'>");
  client.println("</form>");
  
  client.println("</body>");
  client.println("</html>");
  delay(1);
  client.stop();
}

void radiohtml(EthernetClient client) {
  if(digitalRead(RED)>0){
    client.println("<p><input type = 'radio' name = 'led_status' value = '1' checked />RED</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '2' />GREEN</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '3' />BLUE</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '4' />OFF</p>");
  } else if(digitalRead(GREEN)>0){
    client.println("<p><input type = 'radio' name = 'led_status' value = '1' />RED</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '2' checked/>GREEN</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '3' />BLUE</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '4' />OFF</p>");
  } else if(digitalRead(YELLOW)>0){
    client.println("<p><input type = 'radio' name = 'led_status' value = '1' />RED</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '2' />GREEN</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '3' checked />BLUE</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '4' />OFF</p>");
  } else {
    client.println("<p><input type = 'radio' name = 'led_status' value = '1' />RED</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '2' />GREEN</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '3' />BLUE</p>");
    client.println("<p><input type = 'radio' name = 'led_status' value = '4' checked />OFF</p>");
  }
}
