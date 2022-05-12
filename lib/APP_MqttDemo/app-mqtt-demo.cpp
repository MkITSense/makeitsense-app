#include "Arduino.h"
#include <WiFiManager.h>
#include <MKS_Display.h>
#include <PubSubClient.h>
#include <MKS_Clock.h>

// Generar purpose
String chipId;
MKS_Display display;
WiFiManager wifiManager;

// MQTT
WiFiClient mqttWifiClient;
PubSubClient mqttClient(mqttWifiClient);
const char* PUB_TOPIC = "testTopic";
const char* SUB_TOPIC = "";
const char* MQTT_SERVER = "192.168.4.1";
String mqttLastMsgReceived = "";
char mqttLastMsgSent[50];
char mqttMsg[50];
int mqttValue = 0;
MKS_Clock mqttClock;
MKS_Clock mqttClockLastSent;
MKS_Clock mqttClockLastReceived;


char* getAsCharArray(String value) {
  char cValue[value.length()+1];
  value.toCharArray(cValue, value.length());
  return cValue;
}

String getWifiStatus() {
  if(WiFi.status() == WL_CONNECTED) {
    int rssi = WiFi.RSSI();
    return "WIFI: " + String(rssi);
  }
  
  return  "WIFI: ---";
}

String getMqttStatus() {
  if(!mqttClient.connected()) {
    return "MQTT: ---";
  }

  return "MQTT: OK";
}

void updateMqttMessages() {
  if(mqttClockLastReceived.getSeconds() > 3) {
    mqttLastMsgReceived = "";
    mqttClockLastReceived.pause();
  }

    if(mqttClockLastSent.getSeconds() > 3) {
    strcpy(mqttLastMsgSent, "");
    mqttClockLastSent.pause();
  }
}

void updateDisplay() {
  updateMqttMessages();
  display.clear();
  display.print(chipId, 1, 1);
  display.print("[R] " + mqttLastMsgReceived, 2, 1);
  display.print("[S] " + String(mqttLastMsgSent), 3, 1);
  display.print(getWifiStatus() + " " + getMqttStatus(), 4, 1);
  display.updateProgressBar();
  display.show();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String sPayload = String((char *)payload);
  mqttLastMsgReceived = sPayload.substring(0, length);

  mqttClockLastReceived.start();
  updateDisplay();
  delay(500);
}

void mqttPub() {
  if(mqttClock.getSeconds() > 2) {
    ++mqttValue;
    if(mqttValue > 100) {
      mqttValue = 0;
    }

    String sValue = String(mqttValue);
    sValue.toCharArray(mqttLastMsgSent, sValue.length() + 1);
    mqttClient.publish(PUB_TOPIC, mqttLastMsgSent);
    mqttClockLastSent.start();
    updateDisplay();
    mqttClock.start();
  }
}

void mqttSub() {
  if(String(SUB_TOPIC) != "") {
    mqttClient.subscribe(SUB_TOPIC);
  }
}

void mqttReconnect() {
  updateDisplay();

  while (!mqttClient.connected()) {
    updateDisplay();
    
    char charBuf[chipId.length()];
    chipId.toCharArray(charBuf, chipId.length());
    
    if (mqttClient.connect(charBuf)) {
      mqttClock.start();
      mqttSub();
      updateDisplay();
    } 
    else {
      updateDisplay();
      delay(5000);
    }
  }
  updateDisplay();
}

void setup() {
  Serial.begin(9600);
  chipId = "MKIT-" + String(ESP.getChipId());
  WiFi.begin("R2D2-IoT", "carlo$2005");             
  display.start();
  updateDisplay();

  wifiManager.setTimeout(120);

  if(!wifiManager.autoConnect(getAsCharArray(chipId))) {
    updateDisplay();
    ESP.reset();
    delay(1000);
  }
    
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  updateDisplay();
  
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(mqttCallback);

  mqttSub();
  mqttClock.start();
}

void loop() {

  if (!mqttClient.connected()) {
    mqttReconnect();
  }

  mqttClient.loop();

  updateDisplay();


  if(PUB_TOPIC != "") {
    mqttPub();
  }

  delay(500);
}