#ifndef MKS_WifiState_h
#define MKS_WifiState_h

#include "Arduino.h"

class MKS_WifiState
{
public:
    MKS_WifiState(int rssi, boolean connected);
    String getAsString();

private: 
    int _rssi;
    boolean _connected;
};

#endif