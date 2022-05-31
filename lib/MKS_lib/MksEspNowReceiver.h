#include <espnow.h>
#include "MksMessage.h"

class MksEsp32NowReceiver {
    public:
        MksEsp32NowReceiver() {}

        void start(void (*onDataReceived)(const uint8_t *, const uint8_t *, int)) {
            _init();
            _initReceiver(onDataReceived);
        }
            
    private:
        uint8_t *_receiverMacAddress;
        bool _isReceiver;
        bool _isSender;

        bool _init() {
            _isReceiver = false;
            _isSender = false; 

            if (esp_now_init() != 0) {
                Serial.println("Error initializing ESP-NOW");
                return false;
            }

            return true;
        }

        void _initReceiver(void (*onDataReceived)(const uint8_t *, const uint8_t *, int)) {
            esp_now_register_recv_cb(onDataReceived);
            _isReceiver = true;
        }
 
};
