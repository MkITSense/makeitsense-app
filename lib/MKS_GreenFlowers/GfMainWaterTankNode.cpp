#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksMe007DistanceReader.h"
#include "MksEspNowSender.h"
#include "MksMessage.h"
#include "GfNodes.h"

const bool VERBOSE = true;
GfNode RECEIVER_NODE = GF_NODES[DEEP_WEELL_NODE];
const int REFRESH_TIME = 10; // time in seconds
MksMe007DistanceReader sensorReader(4, 13, true);
MksMessage message;
 
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  if(VERBOSE == true) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0) {
      Serial.println("Delivery success");
    } else {
      Serial.println("Delivery fail");
    }
  }

}

MksEspNowSender espNowSender(RECEIVER_NODE.macAddress, OnDataSent, VERBOSE);

void sendData() {
    MksMe007DistanceReader::Reading sensorReading = sensorReader.getReading();

    message.from = GF_NODES[MAIN_WATER_TANK_NODE].id;
    message.values[0] = sensorReading.distance.value;
    message.values[1] = sensorReading.temperature.value;

    espNowSender.send(message);
} 
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifi_set_sleep_type(LIGHT_SLEEP_T);

  if(VERBOSE == true) {
      Serial.println(WiFi.macAddress());
  }
}
 
void loop() {
    sendData();
    delay(10000);
}