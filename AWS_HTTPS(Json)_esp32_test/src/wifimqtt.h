#include <Arduino.h>
#include <ArduinoJson.h>
#include "credentials.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

WiFiClientSecure client;
HTTPClient http;

void reconnect()
{
    
    while (!http.begin(host, Port, uri))
    {
        
        Serial.print("Attampting HTTPS connection............");
        Serial.print(host);

        client.setCACert(AWS_CERT_CA);
        client.setCertificate(AWS_CERT_CRT);
        client.setPrivateKey(AWS_CERT_PRIVATE);
        client.setTimeout(15000); // 15 Seconds
        delay(100);

        Serial.print("HTTPS Connecting to AWS IoT Core\n");

        int r=0; //connection 
        while((!http.begin(host, Port, uri)) && (r < 30)){
            delay(100);
            Serial.print(".");
            r++;
        }
        if(r==30) {
            Serial.println("Connection failed");
        }
        else {
            Serial.println("Connected");
        }
    }
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
