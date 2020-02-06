#include <SPI.h>
#include <Ethernet.h>
byte MAC[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//192.168.2.4
IPAddress IP(192,168,2,200); 
void setup() {
  Serial.begin(9600);
  if(Ethernet.begin(MAC)==0){
    Serial.println("실패");
  }
}

void loop() {
  IPAddress address;
  Serial.print("ip주소:");
  address=Ethernet.localIP();
  print_address(address);  
}

void print_address(IPAddress address){
  for(int i=0; i<4; i++){
    Serial.print(address[i],DEC);
    if(i!=3){
      Serial.print(".");
    }
  }
  delay(60000);
  Serial.println();
}
//ip주소192.168.2.75
