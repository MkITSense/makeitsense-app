#ifndef MKS_WifiState_h
#define MKS_WifiState_h

#include "Arduino.h"

class MKS_WifiState
{
public:
    MKS_WifiState(String chipId, int rssi, boolean connected);
    String getAsString();

private: 
    String _chipId;
    int _rssi;
    boolean _connected;
    String _getConnectionStateMessage();
};

#endif