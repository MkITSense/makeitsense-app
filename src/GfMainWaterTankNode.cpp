#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksMe007DistanceReader.h"
#include "MksClock.h"
#include "MksEspNowSender.h"
#include "MksMessage.h"
#include "MksUnits.h"
#include "GfNodes.h"

GfNode RECEIVER_NODE = GF_NODES[DEEP_WEELL_NODE];
const int REFRESH_TIME = 10; // time in seconds
MksMe007DistanceReader distanceReader(4, 13, true);
MksClock distanceReaderClock;
MksMessage message;
 
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

MksEspNowSender espNowSender(RECEIVER_NODE.macAddress, OnDataSent);

void sendData() {
    MksMe007DistanceReader::Reading distanceReading = distanceReader.getReading();
    distanceReaderClock.start();

    message.from = RECEIVER_NODE.id;
    message.values[0] = distanceReading.distance.value;
    message.values[1] = distanceReading.temperature.value;

    espNowSender.send(message);
} 
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  distanceReaderClock.start();
  Serial.println(WiFi.macAddress());
}
 
void loop() {
    sendData();
    delay(10000);
}