#define analogPin A0
#define ledPin1 11
#define ledPin2 9

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  int ledValue = map(sensorValue, 0,1023, 0,255);

  ledValue = constrain(ledValue, 0,255);

  Serial.println(ledValue);
  
  analogWrite(ledPin1, ledValue);
  analogWrite(ledPin2, 255-ledValue);
  delay(30);
}
