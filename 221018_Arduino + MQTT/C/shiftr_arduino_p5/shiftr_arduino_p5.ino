
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#define inputPin A0
#define outputPin 11

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
int xPos = 100;
int yPos = 100;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outputPin, OUTPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }

  pinMode(inputPin, INPUT);
  
  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  //change this to match your instance name
  client.begin("good7.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  int input = analogRead(inputPin);
  input = map(input, 0, 1023, 0, 300);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    //make sure you add comma after the string e.x. posX, 
    client.publish("/posX", "posX," + String(xPos));
    client.publish("/posY", "posY," + String(yPos));
    client.publish("/diameter", "diameter," + String(input));
    
    //you can also send the message formatted as json
    //client.publish("/pos", "{\"x\":" + String(xPos)+ ",\"y\":" + String(yPos) + "}");
    
    if (xPos < 500){
        xPos += 10;
        yPos += 5;
    } else {
        xPos = 100;
        yPos = 100;
    }
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  if(topic == "ledBlink"){
  int blinkVal = constrain(payload.toInt(), 0, 1);
  digitalWrite(LED_BUILTIN, blinkVal);
  }else if(topic == "slider"){
    int ledOut = map(payload.toInt(), 0,300, 0,255);
    analogWrite(outputPin,ledOut );
  }
}

void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  //change this to match your instance
  while (!client.connect("arduino", "good7", "Jg4YCb4x9pAricO1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  client.subscribe("ledBlink");
  client.subscribe("slider");
}


  
