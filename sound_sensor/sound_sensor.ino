int volumn; 
int led = 9;
int threshold = 540;
int pin = 7;

void setup() {  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {  
  volumn = analogRead(A0);
  Serial.println(volumn, DEC);
  delay(100);
  if(volumn >= threshold){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
