const int led = 9;
void setup() {  
  pinMode(led,OUTPUT);
  Serial.begin(9600); //9600dps 속도로 
  
}

void loop() {
  for(int i  = 100; i<=1000; i+=100){
    digitalWrite(led,HIGH);  
    
    delay(i);
    digitalWrite(led,LOW);
    delay(i);
    //Serial.print("켜짐--");
    //Serial.println(i);
    Serial.print(String("꺼짐")+i);    
  }
}
