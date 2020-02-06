#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN  7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() { 
  Serial.begin(9600);
  dht.begin();
  pinMode(2,OUTPUT);
}

void loop() {  
  delay(2000);
  float h = dht.readHumidity(); // 습도 측정 함수
  float t = dht.readTemperature(); // 온도 측정 (섭씨);
  float f = dht.readTemperature(true);
  if(isnan(h) || isnan(t) || isnan(f)){
    Serial.println("온도 센서 측정 오류");
  }
  float hif = dht.computeHeatIndex(f,h); // 보정된 화씨 값을 가져옵니다.
  float hic = dht.computeHeatIndex(t,h,false); // 보정된 섭씨 값을 가져옵니다.

  if(hic > 30){
    digitalWrite(2,HIGH);
  } else {
    digitalWrite(2,LOW);
  }
//  Serial.println(String("습도: ")+h);
//  Serial.println(String("온도: ")+t);
//  Serial.println(String("온도(화씨): ")+f);
  Serial.println(String("보정된 온도: ")+hic);
  Serial.println(String("보정된 온도(화씨): ")+hif);
}
