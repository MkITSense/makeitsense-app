#include <espnow.h>
#include "MksMessage.h"

class MksEspNowReceiver {
    public:
        MksEspNowReceiver() {}

        void start(void (*onDataReceived)(uint8_t *, uint8_t *,  uint8_t)) {
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

        void _initReceiver(void (*onDataReceived)(uint8_t *, uint8_t *, uint8_t)) {
            esp_now_register_recv_cb(onDataReceived);
            _isReceiver = true;
        }
 
};
