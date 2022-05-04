#include "Arduino.h"
#include <MKS_Display.h>
#include <DNSServer.h>
#include <WiFiManager.h>

String chipId;
MKS_Display display;
WiFiManager wifiManager;

String getConnectionStateMessage() {
  if(WiFi.status() == WL_CONNECTED) {
    return "=";
  } else {
    return "X";
  }
}

String getWifiStateMessage() {
  String rssi = String(WiFi.RSSI());
  String state = getConnectionStateMessage();

  return chipId + " " + rssi + " " + state;
}

void updateDisplay() {
    String wifiState = getWifiStateMessage();    
    display.clear();
    display.print(wifiState, 1, 1);
    //display.print(msg, 2, 1);
    display.updateProgressBar();
    display.show();
}

char* getAccessPointName() {
  char apName[chipId.length()+1];
  chipId.toCharArray(apName, chipId.length());

  return apName;
}

void startWifi() {
  updateDisplay();

  if(!wifiManager.autoConnect(getAccessPointName())){
    updateDisplay();
    Serial.println("Fallo en la conexión (timeout)");
    ESP.reset();
    delay(1000);
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  updateDisplay();
}

void setup() {
  Serial.begin(9600);
  chipId = "MKIT-" + String(ESP.getChipId());
  display.start();
  startWifi();  
}

void loop() {
  updateDisplay();
  delay(500);
}