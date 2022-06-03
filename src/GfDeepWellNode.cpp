#include <ESP8266WiFi.h>
#include <espnow.h>
#include <math.h>
#include "MksDisplay.h"
#include "MksEspNowReceiver.h"
#include "MksUnits.h"
#include "GfNodes.h"
#include "MksClock.h"

MksDisplay display;
MksClock timer;
MksClock timer2;

MksMessage message;
Temperature temperature;
Cube waterTank(100, 100, 120, 29);
String displayValue = "...";

void updateDisplayValue() {
  int seconds = (int)timer.getSeconds();

  if(seconds < 3) {
    displayValue = temperature.getCelsiusAsString();
  } else if(seconds < 6) {
    displayValue = String(round(message.values[0]));
  } else if(seconds < 10) {
    displayValue = waterTank.getFillPercentageAsString();
  } else {
    displayValue = "...";
  }
}

void updateDisplay() {
  updateDisplayValue();
  display.clear();
  display.print(timer2.getCurrentTimeAsString(), 1, 1);
  display.print(displayValue, 2, 3);
  display.updateProgressBar();
  display.show();
}

void onDataReceived(uint8_t * mac, uint8_t *incomingData,  uint8_t len) {
  memcpy(&message, incomingData, sizeof(message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance: ");
  Serial.println(message.values[0]);

  if(message.from == GF_NODES[MAIN_WATER_TANK_NODE].id) {
    temperature.setCelsius(message.values[1]);
    waterTank.setCurrentLevelCm(round(message.values[0]));
    timer.start(); 
  }

}
 
MksEspNowReceiver espNowReceiver;
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  espNowReceiver.start(onDataReceived);
  Serial.println(WiFi.macAddress());
  timer.start();
  timer2.start();
  display.start();
}
 
void loop() {
  updateDisplay();
  delay(500);
}
