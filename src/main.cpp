#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

#define LED_2 27
#define LED_4 26
#define LED_6 25

int i;
bool ledStates[][3]=
{{false,false,false}, 
{false,false,true},
{false,true,false},
{false,true,true},
{true,false,false},
{true,true,false},
{true,false,true},
{true,true,true}};

const int NUM_OF_STATES = sizeof (ledStates) / sizeof (ledStates[0]);

void setup() {
  pinMode(LED_2, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_6, OUTPUT);

  Serial.begin(9600);
	
  WiFi.begin(ssid, password);//ssid and password defined in env.h

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(host);//endpoint "host" defined in env.h
    
    for(i=0;i<NUM_OF_STATES;i++) {
      http.addHeader("X-API-Key", apiKey);//"apiKey" defined in env.h
      http.addHeader("Content-type", "application/json");

      StaticJsonDocument<76> doc;
      String httpRequestData;

      digitalWrite(LED_2, ledStates[i][0]);
      digitalWrite(LED_4, ledStates[i][1]);
      digitalWrite(LED_6, ledStates[i][2]);

      doc["led_2"] = ledStates[i][0];
      doc["led_4"] = ledStates[i][1];
      doc["led_6"] = ledStates[i][2];

      serializeJson(doc, httpRequestData);
      int httpResponseCode = http.PUT(httpRequestData);
      String http_response;

      if(httpResponseCode > 0) {
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);
        Serial.print("Response from server");
        http_response = http.getString();
        Serial.println(http_response);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      delay(2000);
    }

    http.end();
  }   
}
