#include <espnow.h>
#include "MksMessage.h"

class MksEsPNow {
    public:
        MksEspNow() {}

        MksEspNow(void (*onDataReceived)(const uint8_t *, const uint8_t *, int)) {
            _init();
            esp_now_register_recv_cb(onDataReceived);
            _isReceiver = true;
        }
        
        MksEspNow(uint8_t *receiverMacAddress, void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus)) {
            _init();

            if(receiverMacAddress != null && onDataSent != null {
                esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
            } else if(onDataSent !== null) {
                esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            }

            _peerAddress = receiverMacAddress;

            if(onDataSent != null) {
                esp_now_register_send_cb(onDataSent);
            }

            if(_peerAddress != null) {
                esp_now_add_peer(_receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
            }

            if(onDataReceived != null) {
                esp_now_register_recv_cb(callback);
            }
    
        }
        
        MksEspNow(uint8_t *receiverMacAddress, void (*onDataReceived)(const uint8_t*, const uint8_t*, int)) {

            if(receiverMacAddress != null && onDataSent != null {
                esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
            } else if(onDataSent !== null) {
                esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            }

            _peerAddress = receiverMacAddress;

            if(onDataSent != null) {
                esp_now_register_send_cb(onDataSent);
            }

            if(_peerAddress != null) {
                esp_now_add_peer(_receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
            }

            if(onDataReceived != null) {
                esp_now_register_recv_cb(callback);
            }
    
        }
            
        void send(MksMessage message) {
            esp_now_send(_peerAddress, (uint8_t *) &message, sizeof(message));
        }

        MksEspNow(uint8_t *receiverMacAddress, void (*onDataReceived)(const uint8_t*, const uint8_t*, int), void (*onDataSent)(uint8_t *, uint8_t)) {
            if (esp_now_init() != 0) {
                Serial.println("Error initializing ESP-NOW");
                return;
            }

            if(receiverMacAddress != null && onDataSent != null {
                esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
            } else if(onDataSent !== null) {
                esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            }

            _peerAddress = receiverMacAddress;

            if(onDataSent != null) {
                esp_now_register_send_cb(onDataSent);
            }

            if(_peerAddress != null) {
                esp_now_add_peer(_receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
            }

            if(onDataReceived != null) {
                esp_now_register_recv_cb(callback);
            }
    
        }
            
        void send(MksMessage message) {
            esp_now_send(_peerAddress, (uint8_t *) &message, sizeof(message));
        }

    private:
        uint8_t *_peerAddress;
        bool _isReceiver;
        bool _isSender; 
        MksEspNowType _type;

        bool _isSender() {
            if(_receiverMacAddress != null) {
                return true;
            }

            return false;
        }

        bool _isReceiver() {
            if(_onDataReceived != null) {
                return true;
            }

            return false;
        }

        bool _hasSenderListener() {
            if(_isSender() && _onDataSent != null) {
                return true;
            }

            return false;
        }

        void _setIsReceiver() {

        }

        void _isSender() {

        }

        bool _init() {
            if (esp_now_init() != 0) {
                Serial.println("Error initializing ESP-NOW");
                return false;
            }

            return true;
        }
    

};



