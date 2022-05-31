#include <esp_now.h>
#include <WiFi.h>
#include <MksDisplay.h>
#include "MksEsp32NowReceiver.h"

MksDisplay display;

MksMessage message;

void updateDisplay() {
    display.clear();
    display.print(String(message.readings[0].value), 2, 3);
    display.updateProgressBar();
    display.show();
}

void onDataReceived(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&message, incomingData, sizeof(message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance: ");
  Serial.println(message.readings[0].value);
}
 
 MksEsp32NowReceiver espNowReceiver;
 
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
