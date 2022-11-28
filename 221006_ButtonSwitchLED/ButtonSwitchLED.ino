#define inputPin 10
int lastValue = 0;
int ledState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int pinValue = digitalRead(inputPin);

  if(pinValue == 1 && lastValue == 0){
    Serial.println("changed");
      ledState = !ledState;
      
  }
  digitalWrite(13, ledState);
  lastValue = pinValue;
 
  delay(100);

  
}
