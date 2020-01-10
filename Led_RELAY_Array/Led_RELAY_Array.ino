#define DELAY_TIME 100
int led_pin[] = {2, 3, 4, 5, 6};
int state = 0;
void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(led_pin[i], OUTPUT);
  }
  Serial.begin(9600); //9600dps 속도로
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led_pin[i], HIGH);
    delay(1000);
    digitalWrite(led_pin[i], LOW);
    Serial.println(led_pin[i]);
  }
}
