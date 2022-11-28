#define MOTOR_PIN_LEFT_A 7
#define MOTOR_PIN_LEFT_B 8

#define MOTOR_PIN_RIGHT_A 10
#define MOTOR_PIN_RIGHT_B 9

const int FORWARD = 0;
const int RIGHT = 1;
const int LEFT = 2; 
const int REVERSE = 3;
const int STOP = 4;

int myState;

//======================================================================================
// Light sensor
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

//======================================================================================
// Distance sensor
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

DFRobot_VL53L0X sensor;
int lastDistance = 3000;

//======================================================================================

void switchState();
void setupLightSensor();
void setupPins();
void setupDistanceSensor();
int chooseDirection();

//======================================================================================

int direction = LEFT;

void setup() {
  Serial.begin(9600);
  setupPins();
  setupLightSensor();
  setupDistanceSensor();
}

void loop() {

    if(millis() % 23 == 0){
        direction = chooseDirection();
     }
     
    uint16_t r, g, b, c;
     //wait for color data to be ready
    while(!apds.colorDataReady()){
        delay(5);
    }
    apds.getColorData(&r, &g, &b, &c);

    int distance  = sensor.getDistance();
    //Serial.print("Distance: ");
    //Serial.println(distance);

    //Serial.print("R: ");
    //Serial.println(r);

     if( r > 100 ) {
        switchState(STOP);
        delay(5000);
    }

    if (distance < 1000 && distance > 200){
        switchState(direction);
    } else if (distance < 200){
      switchState(REVERSE);
      delay(1000);
      switchState(direction);
      delay(250);
    } else {
        switchState(FORWARD);
    }
}



int chooseDirection(){
  if(millis() % 2){
      return LEFT;
  }else {
      return RIGHT;
  }
}

void switchState(byte state) {

  Serial.println(state);

  switch (state) {
    case STOP:
    
    digitalWrite(MOTOR_PIN_LEFT_A, LOW);
    digitalWrite(MOTOR_PIN_LEFT_B, LOW);
  
    digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
    digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
    break;
    
   case FORWARD:
      digitalWrite(MOTOR_PIN_LEFT_A, HIGH);
      digitalWrite(MOTOR_PIN_LEFT_B, LOW);
    
      digitalWrite(MOTOR_PIN_RIGHT_A, HIGH);
      digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
    break;

     case LEFT:
        digitalWrite(MOTOR_PIN_LEFT_A, LOW);
        digitalWrite(MOTOR_PIN_LEFT_B, LOW);
      
        digitalWrite(MOTOR_PIN_RIGHT_A, HIGH);
        digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
      break;

     case RIGHT:
        digitalWrite(MOTOR_PIN_LEFT_A, HIGH);
        digitalWrite(MOTOR_PIN_LEFT_B, LOW);
      
        digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
        digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
      break;

    case REVERSE:
      digitalWrite(MOTOR_PIN_LEFT_A, LOW);
      digitalWrite(MOTOR_PIN_LEFT_B, HIGH);
    
      digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
      digitalWrite(MOTOR_PIN_RIGHT_B, HIGH);
  break;
  }
}

void setupLightSensor() {

  if(!apds.begin()){
    Serial.println("Adafruit_APDS9960: failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Adafruit_APDS9960: Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void setupDistanceSensor() {
  //join i2c bus (address optional for master)
  Wire.begin();
  //Set I2C sub-device address
  sensor.begin();
  //Set to Back-to-back mode and high precision mode
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  //Laser rangefinder begins to work
  sensor.start();
}


void setupPins(){
  //Motor pins
  pinMode(MOTOR_PIN_LEFT_A, OUTPUT);
  pinMode(MOTOR_PIN_LEFT_B, OUTPUT);

  pinMode(MOTOR_PIN_RIGHT_A, OUTPUT);
  pinMode(MOTOR_PIN_RIGHT_B, OUTPUT);
}
