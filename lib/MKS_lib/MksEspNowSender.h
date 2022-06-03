#include <espnow.h>
#include "MksMessage.h"

class MksEspNowSender {
    public:      
        MksEspNowSender(const uint8_t receiverMacAddress[], void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus), bool verbose) {
            _verbose = verbose;
            _init();
            _initSender(receiverMacAddress, onDataSent);
        }
            
        void send(MksMessage message) {
            if(_isSender == true) {

                if(_verbose == true) {
                    Serial.print("Receiver: ");
                    Serial.println((char*)_receiverMacAddress);
                    Serial.print("From: ");
                    Serial.println(message.from);
                    Serial.print("id: ");
                    Serial.println(message.values[0]);
                }
    
                esp_now_send(_receiverMacAddress, (uint8_t *) &message, sizeof(message));
            }
        }

    private:
        uint8_t _receiverMacAddress[6];
        bool _isReceiver;
        bool _isSender;
        bool _verbose;

        bool _init() {
            _isReceiver = false;
            _isSender = false; 

            if (esp_now_init() != 0) {

                if(_verbose == true) {
                    Serial.println("Error initializing ESP-NOW");
                }
                
                return false;
            }

            return true;
        }

        void _initSender(const uint8_t *receiverMacAddress, void (*onDataSent)(uint8_t *mac_addr, uint8_t sendStatus)) {
            _receiverMacAddress[0] = receiverMacAddress[0];
            _receiverMacAddress[1] = receiverMacAddress[1];
            _receiverMacAddress[2] = receiverMacAddress[2];
            _receiverMacAddress[3] = receiverMacAddress[3];
            _receiverMacAddress[4] = receiverMacAddress[4];
            _receiverMacAddress[5] = receiverMacAddress[5];


            //_receiverMacAddress = receiverMacAddress;
            esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
            esp_now_register_send_cb(onDataSent);
            esp_now_add_peer(_receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
            _isSender = true;
        }    
};



