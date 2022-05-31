#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksDisplay.h"
#include "MksEspNowReceiver.h"

MksDisplay display;

MksMessage message;

void updateDisplay() {
    display.clear();
    display.print(String(message.values[0]), 2, 3);
    display.updateProgressBar();
    display.show();
}

void onDataReceived(uint8_t * mac, uint8_t *incomingData,  uint8_t len) {
  memcpy(&message, incomingData, sizeof(message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance: ");
  Serial.println(message.values[0]);
}
 
 MksEspNowReceiver espNowReceiver;
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  espNowReceiver.start(onDataReceived);
  Serial.println(WiFi.macAddress());
  display.start();
}
 
void loop() {
   updateDisplay();
    delay(200);
}
