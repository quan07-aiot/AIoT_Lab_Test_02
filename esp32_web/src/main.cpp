#include <Arduino.h>
#include <WiFi.h>
#include "car.h"
#include "web_server.h"

const char *ssid = "Test";
const char *password = "09876543";

void setup() {
  Serial.begin(115200); 
  carInit();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Connected...good");
  Serial.println(WiFi.localIP());    // địa chỉ để gõ vào trình duyệt

  serverInit();
}

void loop() {
  serverRun();
}