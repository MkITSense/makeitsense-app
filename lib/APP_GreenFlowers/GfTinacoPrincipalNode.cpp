#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksMe007DistanceReader.h"
#include "MksClock.h"
#include "MksNowSender.h"
#include "MksMessage.h"
#include "GfNodes.h"

const int REFRESH_TIME = 10 // time in seconds
MksMe007DistanceReader distanceReader(5, 13, true);
MksClock distanceReaderClock;
MksNowSender sender(MAIN_NODE);
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

void sendData() {
    MksMe007DistanceReader::Reading distanceReading = distanceReader.getReading();
    distanceReaderClock.start();

    MksMessage message;
    message.from = MAIN_NODE;
    message.id = 1;
    message.numValues = 2;
    message.values = new MksSensorValue[2];
    message.values[0] = distanceReading.distance;
    message.values[1] = distanceReading.temperature;

    sender.send(message);
} 
 
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  sender.start(OnDataSent);
  distanceReaderClock.start();
}
 
void loop() {

  if(distanceReaderClock.getSeconds() >= REFRESH_TIME) {
    sendData();
  }

  ESP.deepSleep(10e6);
}