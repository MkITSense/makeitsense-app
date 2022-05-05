#include "Arduino.h"
#include "MKS_WifiState.h"

MKS_WifiState::MKS_WifiState(String chipId, int rssi, boolean connected) {
    _chipId = chipId;
    _rssi = rssi;
    _connected = connected;
}

String MKS_WifiState::_getConnectionStateMessage() {
    if(_connected == true) {
        return "OK";
    } else {
        return "NC";
    }
}

String MKS_WifiState::getAsString() {
    String rssi = String(_rssi);
    String state = MKS_WifiState::_getConnectionStateMessage();
    
    return _chipId + " " + rssi + " " + state;
}