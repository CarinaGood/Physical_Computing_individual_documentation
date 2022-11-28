#define MOTOR_PIN_LEFT_A 7
#define MOTOR_PIN_LEFT_B 8

#define MOTOR_PIN_RIGHT_A 10
#define MOTOR_PIN_RIGHT_B 9

#define analogPin A0

const byte FORWARD = 0;
const byte RIGHT = 1;
const byte LEFT = 2; 
const byte REVERSE = 3;
const byte STOP = 4;

byte myState;


void setup() 
{
  Serial.begin(9600);
  myState = FORWARD;  // Initial State

  pinMode(analogPin, INPUT);
  
  pinMode(MOTOR_PIN_LEFT_A, OUTPUT);
  pinMode(MOTOR_PIN_LEFT_B, OUTPUT);

  pinMode(MOTOR_PIN_RIGHT_A, OUTPUT);
  pinMode(MOTOR_PIN_RIGHT_B, OUTPUT);
}
void loop() 
{
  int analogValue = analogRead(analogPin);
  Serial.println(analogValue);
  if(0 < 200){
    myState = REVERSE;
  } else if ( analogValue > 200 && analogValue < 400){
    myState = LEFT;
  }else if ( analogValue > 400 && analogValue < 600){
    myState = RIGHT;
  }else if ( analogValue > 600 && analogValue < 800){
    myState = FORWARD;
  }else{
    myState = STOP;
   }
  
  switch (myState) {
    case STOP:
    Serial.println("Stop");
    digitalWrite(MOTOR_PIN_LEFT_A, LOW);
    digitalWrite(MOTOR_PIN_LEFT_B, LOW);
  
    digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
    digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
    delay(500);
    break;
     case FORWARD:
        //One direction
        Serial.println("Enter FORWARD state");
        digitalWrite(MOTOR_PIN_LEFT_A, HIGH);
        digitalWrite(MOTOR_PIN_LEFT_B, LOW);
      
        digitalWrite(MOTOR_PIN_RIGHT_A, HIGH);
        digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
        delay(500);
      break;

     case LEFT:
        //One direction
        Serial.println("Enter LEFT state");
        digitalWrite(MOTOR_PIN_LEFT_A, LOW);
        digitalWrite(MOTOR_PIN_LEFT_B, LOW);
      
        digitalWrite(MOTOR_PIN_RIGHT_A, HIGH);
        digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
        delay(500);
      break;

     case RIGHT:
        //One direction
        Serial.println("Enter RIGHT state");
        digitalWrite(MOTOR_PIN_LEFT_A, HIGH);
        digitalWrite(MOTOR_PIN_LEFT_B, LOW);
      
        digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
        digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
        delay(500);
      break;

    case REVERSE:
      Serial.println("Enter REVERSE state");
      digitalWrite(MOTOR_PIN_LEFT_A, LOW);
      digitalWrite(MOTOR_PIN_LEFT_B, HIGH);
    
      digitalWrite(MOTOR_PIN_RIGHT_A, LOW);
      digitalWrite(MOTOR_PIN_RIGHT_B, HIGH);
      delay(500);
  break;
  }
}
