#include <ESP8266WiFi.h>
#include <espnow.h>
#include "MksMe007DistanceReader.h"
#include "MksClock.h"
#include "MksNowSender.h"

MksMe007DistanceReader distanceReader(5, 13, 4);
MksClock distanceReaderClock;

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress2[] = {0x24, 0x6F, 0x28, 0x44, 0xE6, 0xB8}; // ESP32
uint8_t broadcastAddress[] = {0x5C, 0xCF, 0x7F, 0x8C, 0x8D, 0xAE}; 


MksNowSender sender(broadcastAddress2);
MksNowSender::Message myData;


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

   myData.b = 0;
  
  sender.start(OnDataSent);
  distanceReaderClock.start();
}
 
void loop() {

  if(distanceReaderClock.getSeconds() >= 2) {
    MksMe007DistanceReader::Reading distanceReading = distanceReader.getReading();
    distanceReaderClock.start();

     // Set values to send
    strcpy(myData.a, "THIS IS A CHAR");
    myData.b = myData.b + 1;
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = false;

    if(myData.b >= 10) {
      myData.b = 0;
    }

    sender.send(myData);
  }

}