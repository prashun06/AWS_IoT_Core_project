#include <Arduino.h>
#include <ArduinoJson.h>
#include <wifimqtt.h>

unsigned long previousMillis=millis();

void sendMQTTvalues(){ // send the json data from esp to nodered 
  StaticJsonDocument<96> doc;

  doc["device"] = "ESP MCU";
  doc["temperature"] = 33;
  doc["humidity"] = 90;
  doc["lux"] = 643;
  
  char buff[256];
  serializeJson(doc, buff); 
  client.publish("AWS-IOT",buff);
}

void setup() {
  Serial.begin(115200);
  //pinMode(led,OUTPUT);
  connectAP();
  client.setServer(awsEndpoint, 8883);
  client.setCallback(msgReceived);
}

void loop() 
{
  if(!client.connected()){
    reconnect();
  }
  if(!client.loop()){
    client.connect("ESP32-1");
  }

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 5000){
    previousMillis = currentMillis;
    //digitalWrite(led,!digitalRead(led));
    //client.publish("toNodeRED","Hellow from esp32"); // it will send the data to mosquitto broker 
    sendMQTTvalues();
  }
}
