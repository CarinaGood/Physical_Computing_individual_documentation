#define sensorPin A0
#define ledPin 9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0,1023,0,255);
  sensorValue = constrain(sensorValue,0,255);
  sensorValue = 255 - sensorValue;

Serial.println(sensorValue);
analogWrite(ledPin, sensorValue);
delay(50);
}
