#include "Arduino.h"
#include "MKS_Wifi.h"

void MKS_WIFI::setup(long chipId, MKS_display display) {
    _chipId = chipId;
    _display = display;
}

void MKS_WIFI::startWifi() {
    MKS_Wifi::_updateDisplay();
    
    if(!_wifiManager.autoConnect(MKS_Wifi::_getAccessPointName())) {
        MKS_Wifi::_updateDisplay();
        Serial.println("Fallo en la conexión (timeout)");
        ESP.reset();
        delay(1000);
    }
    
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    
    MKS_Wifi::updateDisplay();
}

void MKS_WIFI::check() {
    MKS_Wifi::_updateDisplay();
}

String MKS_WIFI::_getConnectionStateMessage() {
    if(WiFi.status() == WL_CONNECTED) {
        return "=";
    } else {
        return "X";
    }
}

String MKS_WIFI::_getWifiStateMessage() {
    String rssi = String(WiFi.RSSI());
    String state = MKS_Wifi::_getConnectionStateMessage();
    
    return chipId + " " + rssi + " " + state;
}

void MKS_WIFI::_updateDisplay() {
    String wifiState = MSK_WIFI::_getWifiStateMessage();    
    _display.clear();
    _display.print(wifiState, 1, 1);
    _display.updateProgressBar();
    _display.show();
}

char* MKS_WIFI::_getAccessPointName() {
    char apName[chipId.length()+1];
    _chipId.toCharArray(apName, _chipId.length());
    
    return apName;
}