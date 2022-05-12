#include "Arduino.h"
#include "MKS_WifiState.h"

MKS_WifiState::MKS_WifiState(int rssi, boolean connected) {
    _rssi = rssi;
    _connected = connected;
}

String MKS_WifiState::getAsString() {
    String rssi = String(_rssi);
    
    if(_connected == true) {
        return "WIFI: " + rssi;
    } else {
        return "WIFI: ?";
    }
}