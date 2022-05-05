#include "Arduino.h"
#include "MKS_Wifi.h"

void MKS_Wifi::start(String chipId, MKS_Display display) {
    _chipId = chipId;
    _display = display;

    MKS_Wifi::_updateDisplay("Connecting...");
    
    if(!_wifiManager.autoConnect(MKS_Wifi::_getAccessPointName())) {
        MKS_Wifi::_updateDisplay("Connection timeout");
        Serial.println("Fallo en la conexión (timeout)");
        ESP.reset();
        delay(1000);
    }
    
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    
    MKS_Wifi::_updateDisplay("Connected!");
}

 MKS_WifiState MKS_Wifi::getState() {
     boolean connected = false;
     int rssi = WiFi.RSSI();

     if(WiFi.status() == WL_CONNECTED) {
         connected = true;
     }

     return  MKS_WifiState(_chipId, rssi, connected);
}

void MKS_Wifi::_updateDisplay(String msg) {
    _display.clear();
    _display.print(_chipId, 1, 1);
    _display.print("Wifi setup", 2, 1);
    _display.print(msg, 4, 1);
    _display.updateProgressBar();
    _display.show();
}

char* MKS_Wifi::_getAccessPointName() {
    char apName[_chipId.length()+1];
    _chipId.toCharArray(apName, _chipId.length());
    
    return apName;
}