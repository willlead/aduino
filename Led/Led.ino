const int led = 9;
void setup() {  
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  for(int i  = 100; i<=1000; i+=100){
    digitalWrite(led,HIGH);  
    delay(i);
    digitalWrite(led,LOW);
    delay(i);
    Serial.println(i);
  }
}
