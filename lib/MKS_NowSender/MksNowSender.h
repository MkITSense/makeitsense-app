#include <espnow.h>
#include "MksMessage.h"

class MksNowSender {
    public:
       
       MksNowSender(uint8_t *receiverMacAddress) {
                _peerAddress = receiverMacAddress;
        }

        void start(void (*callback)(uint8_t *, uint8_t)) {
            if (esp_now_init() != 0) {
                Serial.println("Error initializing ESP-NOW");
                return;
            }
            
            esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            esp_now_register_send_cb(callback);
            esp_now_add_peer(_peerAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
        }

        void send(MksMessage message) {
            esp_now_send(_peerAddress, (uint8_t *) &message, sizeof(message));
        }

    private:
        uint8_t *_peerAddress; 

};