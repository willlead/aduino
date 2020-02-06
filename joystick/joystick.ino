//조이스틱
//x = A0
//y = A1
//sw = 3
#define RED 11
#define GREEN 10
#define BLUE 9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int push = digitalRead(3);
  int posX = analogRead(A0);
  int posY = analogRead(A1);


  if (posX > 600) {
    digitalWrite(RED, HIGH);
  } else if (posX < 450) {
    digitalWrite(BLUE, HIGH);
  } else if (posY > 600) {
    digitalWrite(GREEN, HIGH);
  }else if (posY < 450) {
    digitalWrite(8, HIGH);
  } else if (push == 0) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(8, LOW);
  }

//  Serial.println(String("버튼상태") + push);
//  Serial.println(String("x값: ") + posX);
//  Serial.println(String("y값: ") + posY);
  delay(100);
}
