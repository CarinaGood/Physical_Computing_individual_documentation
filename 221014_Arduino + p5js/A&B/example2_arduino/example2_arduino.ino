
#define OUTPUT_PIN 11
const int DELAY_MS = 200;
int inputVal;
#include <Servo.h>

Servo myservo;  // create servo object 
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  // Check to see if there is any incoming serial data
  if (Serial.available() > 0) {
    // read string until the endo of the line
    String rcvdSerialData = Serial.readStringUntil('\n');
    String values[] = 
//    pos = map(value, 0, 1, 0,180);
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'

    delay(10);
    //analogWrite(OUTPUT_PIN, rcvdSerialData.toInt());
    delay(DELAY_MS);
  }
}
