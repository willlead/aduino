#include <SPI.h>
#include <Ethernet.h>

byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB};
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);

int LED_pin =3;
int brightness = 0;
String buffer = "";
String valueString;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  delay(2000);
  server.begin();  
  pinMode(LED_pin, OUTPUT);
  analogWrite(LED_pin,brightness); // LED 꺼진 상태로 시작
  
}

void loop() {
  EthernetClient client = server.available(); // 이더넷 통신 시도
  if (client) { //웹브라우저가 홈페이지에 접속한 경우(예: 192.168.2.75)
    //int response_type = -1;
    
    while (client.connected()) {
     boolean empty_line = read_one_line(client);
     Serial.println(buffer);

     int pos = buffer.indexOf("GET /led.cgi?brightness=");
     if(pos>=0){
      valueString = "";
      pos+= 24; // 24를 더한 이유? GET...에기 23자리라...
      int pos_end = -1;
      for(int i =pos; i<buffer.length(); i++){
        if(buffer[i] == ' '){
          pos_end = i;
          break;
        }
      }
      if(pos_end != -1) {
        valueString = buffer.substring(pos, pos_end); // 밝기값.
      }
     }
     if(empty_line) break; // true 면 break; html 요청이 끝나면
    }
    int input = valueString.toInt();
    if(0 <= input && input <= 255){
      brightness = input;
      analogWrite(LED_pin, brightness);
    }
    show_main_page(client);
    client.stop();
  }
}

boolean read_one_line(EthernetClient client){
  buffer = "";
  while(client.available()){
    char c = client.read();
    if(c=='\r'){
      client.read();
      break;
    }
    buffer += c;
  }
  return (buffer.length() == 0); //빈 줄 여부 반환
}


void show_main_page(EthernetClient client) {
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
  
  client.println("LED 밝기 (0~255) is");
  client.print(brightness);
  client.print("(현재밝기)");
  client.println("<br/>");
  client.println("<form method='get' action='/led.cgi'>");
  client.println("<p>밝기 입력 <input type='text' name='brightness' /></p>");
  client.println("<p><input type = 'submit' value='전송'/></p>");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  client.stop();
}
