#include "Arduino.h"
#include <MKS_Display.h>
#include <MKS_Wifi.h>
#include <MKS_WifiState.h>
#include <PubSubClient.h>

String chipId;
MKS_Display display;
MKS_Wifi wifi;
MKS_WifiState wifiState(0, false);

WiFiClient espClient;
PubSubClient client(espClient);
const char* mqtt_server = "192.168.4.1";
long lastMsg = 0;
char msg[50];
int value = 0;

void updateDisplay(String mqtt) {
  wifiState = wifi.getState();
  display.clear();
  display.print(chipId, 1, 1);
  display.print(wifiState.getAsString() + " MQTT: " + mqtt, 4, 1);
  display.updateProgressBar();
  display.show();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
 
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    updateDisplay("...");
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      updateDisplay("OK");
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  updateDisplay("OK");
}

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(9600);
  chipId = "MKIT-" + String(ESP.getChipId());
  display.start();
  wifi.start(chipId, display); 

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }

  wifiState = wifi.getState();
  updateDisplay("OK");
  delay(500);
}