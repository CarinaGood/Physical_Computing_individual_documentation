
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#define pPin A0

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
unsigned long lastMillis = 0;
int ledBlink; 

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

void setup() {
  pinMode(pPin, INPUT);
  Serial.begin(115200);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }
  
  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  client.begin("good7.cloud.shiftr.io", net);
  connect();
}

void loop() {
  int input = analogRead(pPin);
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
  
    if(ledBlink == 1) {
      ledBlink = 0;
    }else {
      ledBlink = 1;
    }
    client.publish("/potentiometers", String(input));
  }

}


void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  while (!client.connect("carina", "good7", "Jg4YCb4x9pAricO1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  client.subscribe("ledBlink");
}
