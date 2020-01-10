#define DELAY_TIME 100

void setup() {  
  for(int i = 2; i<=6; i++){
    pinMode(i,OUTPUT);  
  }  
  Serial.begin(9600); //9600dps 속도로   
}

void loop() {  
  
  digitalWrite(2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(2,LOW);

  digitalWrite(3, HIGH);
  delay(DELAY_TIME);
  digitalWrite(3,LOW);
  

  digitalWrite(4, HIGH);
  delay(DELAY_TIME);
  digitalWrite(4,LOW);
  

  digitalWrite(5, HIGH);
  delay(DELAY_TIME);
  digitalWrite(5,LOW);
  

  digitalWrite(6, HIGH);
  delay(DELAY_TIME);
  digitalWrite(6,LOW);
  
}
