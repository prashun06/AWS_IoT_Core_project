#include <Arduino.h>
#include <ArduinoJson.h>
#include <wifimqtt.h>

unsigned long previousMillis=millis();

void sendHTTPvalues(){ // send the json data from esp to nodered 
  StaticJsonDocument<96> doc;

  doc["device"] = "ESP MCU";
  doc["temperature"] = 33;
  doc["humidity"] = 90;
  doc["lux"] = 643;

  char buff[256];
  serializeJson(doc, buff);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(buff);
  Serial.println(buff);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}

void setup() {
  Serial.begin(115200);
  //pinMode(led,OUTPUT);
  connectAP();
  if(!client.connected()){
    reconnect();
  }
}

void loop() 
{
  


  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 5000){
    previousMillis = currentMillis;
    sendHTTPvalues();
  }
}
