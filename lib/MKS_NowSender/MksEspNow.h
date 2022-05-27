#include <espnow.h>
#include "MksMessage.h"

class MksEsPNow {
    public:
        MksEspNow() {}

        MksEspNow(void (*onDataReceived)(const uint8_t *, const uint8_t *, int)) {
            _init();
            _initReceiver(onDataReceived)
        }
        
        MksEspNow(uint8_t *receiverMacAddress, void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus)) {
            _init();
            _initSender(receiverMacAddress, onDataSent);
        }
        
        MksEspNow(void (*onDataReceived)(const uint8_t *, const uint8_t *, int), uint8_t *receiverMacAddress, void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus) {
            _init();
            _initReceiver(onDataReceived);
            _initSender(receiverMacAddress, onDataSent);
        }
            
        void send(MksMessage message) {
            if(_isSender == true) {
                esp_now_send(_receiverMacAddress, (uint8_t *) &message, sizeof(message));
            }
        }

    private:
        uint8_t *_peerAddress;
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

        void initReceiver(void (*onDataReceived)(const uint8_t *, const uint8_t *, int)) {
            esp_now_register_recv_cb(onDataReceived);
            _isReceiver = true;
        }

        void initSender(uint8_t *receiverMacAddress, void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus)) {
            _receiverMacAddress = receiverMacAddress;
            esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            _peerAddress = receiverMacAddress;
            esp_now_register_send_cb(onDataSent);
            esp_now_add_peer(_receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
            _isSender = true;
        }    
};



