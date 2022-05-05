#ifndef MKS_Wifi_h
#define MKS_Wifi_h

#include <MKS_Display.h>
#include <MKS_WifiState.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include "Arduino.h"

class MKS_Wifi
{
public:
    void start(String chipId, MKS_Display display);
    MKS_WifiState getState();

private:
    MKS_Display _display;
    WiFiManager _wifiManager;
    String _chipId;
 
    void _updateDisplay(String msg);
    char* _getAccessPointName();
};

#endif