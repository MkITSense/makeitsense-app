#ifndef MKS_Wifi_h
#define MKS_Wifi_h

#include <MKS_Display.h>
#include "Arduino.h"

class MKS_Wifi
{
public:
    void setup(long chipId, MKS_display display);
    void startWifi();
    void check();

private:
    MKS_Display _display;
    WiFiManager _wifiManager;
 
    String _getConnectionStateMessage();
    String _getWifiStateMessage();
    void _updateDisplay();
    char* _getAccessPointName();
};

#endif