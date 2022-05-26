#include <espnow.h>
#include "MksMessage.h"

class MksNowReceiver {
    public:
       MksNowReceiver(uint8_t *receiverMacAddress) {}

       void start(void (*callback)(const uint8_t*, const uint8_t*, int)) {
           if (esp_now_init() != ESP_OK) {
               Serial.println("Error initializing ESP-NOW");
               return;
            }
            esp_now_register_recv_cb(callback);
        }

    private:
        uint8_t *_peerAddress; 

};
