/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"

// Replace with your network credentials
const char* ssid = "Titkov";
const char* password = "17892850";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with button section in your web page
String processor(const String& var){
   
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
 
  // Initialize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/my_page.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });

  // favicon
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/favicon.ico", "image/ico");
  });

  // image
  server.on("/rabbit.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/rabbit.ico", "image/ico");
  });

  // Start server
  server.begin();

}

void loop() {

}