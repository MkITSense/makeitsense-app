#include <esp_now.h>
#include <WiFi.h>
#include <MKS_Display.h>
#include "MksEspNow.h"

MKS_Display display;
MksEspNow espNowReceiver;
MksMessage message;

void updateDisplay() {
    display.clear();
    display.print(String(myNum), 1, 5);
    display.updateProgressBar();
    display.show();
}

void onDataReceived(const uint8_t * mac, const uint8_t *incomingData, int len) {
  mks
  memcpy(&message, incomingData, sizeof(message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance: ");
  Serial.println);

   myNum = myData.b;
}
 
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  display.start();
  espNowReceiver = new MksEsPNow(onDataReceived);
}
 
void loop() {
   updateDisplay();
    delay(200);
}
