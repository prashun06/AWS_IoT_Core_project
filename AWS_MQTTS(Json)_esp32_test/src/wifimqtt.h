#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "credentials.h"
#include <WiFiClientSecure.h>
//#include "main.h"

String clientID = "ESP32-1";

WiFiClientSecure espclient;
PubSubClient client(espclient);

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attampting MQTT connection............");
        Serial.print(awsEndpoint);
        clientID += String(random(0xffff), HEX);

        espclient.setCACert(AWS_CERT_CA);
        espclient.setCertificate(AWS_CERT_CRT);
        espclient.setPrivateKey(AWS_CERT_PRIVATE);

        if (client.connect(clientID.c_str()))
        {
            Serial.print("connect to MQTT");
            client.subscribe("AWS-IOT"); //broker subscription 1
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.print(" try again in 5 sec");
            delay(5000);
        }
    }
}

void msgReceived(char *topic, byte *message, unsigned int length)
{
    String messageTemp;

    for(int i=0; i<length; i++)
    {
        messageTemp += (char)message[i];
    }

    if (String(topic) == "AWS-IOT"){ //subscription 1
        Serial.println(messageTemp);
    }
/*
    else if (String(topic) == "ledState"){ //subscription 2
        Serial.println(messageTemp);
        if(messageTemp == "off"){
            //digitalWrite(led, LOW);
        }
        else if(messageTemp == "on"){
            //digitalWrite(led, HIGH);
        }
    }
    else if (String(topic) == "JSONfromNodeRED"){ //subscription 3 json data hamdle 
    //receive the json data from node red to esp
        StaticJsonDocument<128> doc;

        DeserializationError error = deserializeJson(doc, messageTemp);

        if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
        }

        const char* device = doc["device"]; // "ESP MCU"
        int temperature = doc["temperature"]; // 33
        int humidity = doc["humidity"]; // 90
        int lux = doc["lux"]; // 643

        //print the values
        String output = String(device)+ " " + String(temperature)+ " " + String(humidity)+ " " + String(lux);
        Serial.println(output);
    }
    */
}

void connectAP()
{
    Serial.println("Connect to my WiFi");
    WiFi.begin(ssid, password);
    byte cnt=0;

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
        cnt++;

        if(cnt>30)
        {
            ESP.restart();
        }
    }
}
