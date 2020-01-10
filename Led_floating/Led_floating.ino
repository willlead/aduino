#define LED 9
#define BUTTON 2
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);  
}

void loop() {
  //버튼이 HIGH인 상태 
  if(digitalRead(BUTTON) == HIGH){
    digitalWrite(LED,HIGH);
    delay(2000);
    digitalWrite(LED,LOW);
  } else {
    
  }
}
