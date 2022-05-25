#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksMe007DistanceReader.h"
#include "MksClock.h"
#include "MksNowSender.h"
#include "MksMessage.h"

MksMe007DistanceReader distanceReader(5, 13, true);
MksClock distanceReaderClock;

// REPLACE WITH RECEIVER MAC Address
uint8_t receiverAddress[] = {0x24, 0x6F, 0x28, 0x44, 0xE6, 0xB8}; // ESP32 LilyGo

MksNowSender sender(receiverAddress);
MksMessage message;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  sender.start(OnDataSent);
  distanceReaderClock.start();
}
 
void loop() {

  if(distanceReaderClock.getSeconds() >= 2) {
    MksMe007DistanceReader::Reading distanceReading = distanceReader.getReading();
    distanceReaderClock.start();

    MksMessage message;
    message.from = receiverAddress;
    message.id = 1;
    message.numValues = 2;
    message.values = new MksSensorValue[2];
    message.values[0] = distanceReading.distance;
    message.values[1] = distanceReading.temperature;

    sender.send(message);
  }

}