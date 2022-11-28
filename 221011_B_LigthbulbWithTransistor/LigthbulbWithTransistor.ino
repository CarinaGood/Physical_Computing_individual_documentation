#define ledPin2 9

void setup() {
  Serial.begin(9600);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  analogWrite(ledPin2, 0);
  delay(30);
  analogWrite(ledPin2, 50);
  delay(30);
  analogWrite(ledPin2, 100);
  delay(30);
  analogWrite(ledPin2, 150);
  delay(30);
  analogWrite(ledPin2, 200);
  delay(30);
  analogWrite(ledPin2, 250);
  delay(30);
}
