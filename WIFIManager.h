#include "esp32-hal.h"
#include "HardwareSerial.h"
#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>


class WiFiManager {
  const char* ssid;
  const char* password;

public:
  WiFiManager(const char* wifiName, const char* wifiPassword) {
    ssid = wifiName;
    password = wifiPassword;
  }

  void connect() {
    Serial.print("Connecting to Wifi.....");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  bool isConnected(){
    return WiFi.status() == WL_CONNECTED;
  }
};

#endif