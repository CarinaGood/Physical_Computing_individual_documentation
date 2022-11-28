#define MOTOR_PIN_LEFT_A 7
#define MOTOR_PIN_LEFT_B 8

#define MOTOR_PIN_RIGHT_A 10
#define MOTOR_PIN_RIGHT_B 9



void setup() 
{
  Serial.begin(9600);
  
  pinMode(MOTOR_PIN_LEFT_A, OUTPUT);
  pinMode(MOTOR_PIN_LEFT_B, OUTPUT);

  pinMode(MOTOR_PIN_RIGHT_A, OUTPUT);
  pinMode(MOTOR_PIN_RIGHT_B, OUTPUT);
}

void loop() 
{
 
    Serial.println("Enter FORWARD state");
    digitalWrite(MOTOR_PIN_LEFT_A, HIGH);
    digitalWrite(MOTOR_PIN_LEFT_B, LOW);
  
    digitalWrite(MOTOR_PIN_RIGHT_A, HIGH);
    digitalWrite(MOTOR_PIN_RIGHT_B, LOW);
    delay(500);
     
  
}
