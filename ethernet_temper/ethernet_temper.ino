#include <SPI.h>
#include <Ethernet.h>

#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN  7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB};
IPAddress IP(192, 168, 2, 13);
EthernetServer server(80);

float h, t, f, hic, hif;

void setup() {
  Serial.begin(9600);
  dht.begin();
  //  pinMode(2,OUTPUT);

  Ethernet.begin(MAC, IP); // 이데넷 쉴드 초기화
  server.begin();
  if (Ethernet.begin(MAC) == 0) {
    Serial.println("실패");
  }
}

void loop() {
  delay(2000);
  h = dht.readHumidity(); // 습도 측정 함수
  t = dht.readTemperature(); // 온도 측정 (섭씨);
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("온도 센서 측정 오류");
  }
  hif = dht.computeHeatIndex(f, h); // 보정된 화씨 값을 가져옵니다.
  hic = dht.computeHeatIndex(t, h, false); // 보정된 섭씨 값을 가져옵니다.

  //  if(hic > 30){
  //    digitalWrite(2,HIGH);
  //  } else {
  //    digitalWrite(2,LOW);
  //  }
  //  Serial.println(String("습도: ")+h);
  //  Serial.println(String("온도: ")+t);
  //  Serial.println(String("온도(화씨): ")+f);
  Serial.println(String("보정된 온도: ") + hic);
  Serial.println(String("보정된 온도(화씨): ") + hif);
  EthernetClients();
}

void EthernetClients() { //서버(홈페이지)
  EthernetClient client = server.available(); // 이더넷 통신 시도
  if (client) {
    //    Serial.println("서버와 통신 시작");
    boolean current = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); //서버에 들어온 값을 읽어 들인다.        

        if (c == '\n' && current) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5"); // 5초마다 갱신
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<meta charset = 'utf-8'/>");
          client.println("<title>아두이노 웹서버</title>");
          client.println("</head>");

          client.println("<body>");
          client.println("<h1>우리집에 오신 것을 환영합니다.</h1>");
          client.print("<p>현재 우리집 온도: ");
          client.print(hic);
          client.println("도</p>");
          client.println("<p>==================</p>");
          client.print("<p>현재 우리집 습도: ");
          client.print(h);
          client.println("%</p>");
          client.println("<p>==================</p>");
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
