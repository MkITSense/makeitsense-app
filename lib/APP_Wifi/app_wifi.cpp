#include "Arduino.h"
#include <MKS_Display.h>
#include <MKS_Wifi.h>
#include <MKS_WifiState.h>

String chipId;
MKS_Display display;
MKS_Wifi wifi;
MKS_WifiState wifiState("*", 0, false);

void updateDisplay() {
  display.clear();
  display.print(wifiState.getAsString(), 1, 1);
  display.updateProgressBar();
  display.show();
}

void setup() {
  Serial.begin(9600);
  chipId = "MKIT-" + String(ESP.getChipId());
  display.start();
  wifi.start(chipId, display); 
}

void loop() {
  wifiState = wifi.getState();
  updateDisplay();
  delay(500);
}