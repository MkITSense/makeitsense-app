 #include <SoftwareSerial.h>
#include "MksMessage.h"

class MksMe007DistanceReader {
    public:
        struct Reading {
            MksSensorValue distance; // in centimeters
            MksSensorValue temperature;
        };

        bool VERBOSE;
        int TRIGGER_PIN;
        int RX_PIN; 
        const int TX_PIN = 0; // not used and not connected

        MksMe007DistanceReader(int triggerPin, int rxPin, bool verbose)     {
            TRIGGER_PIN = triggerPin;
            RX_PIN = rxPin;
            VERBOSE = verbose;
        }

        Reading getReading() {
            Reading reading;
            int attempts = 10;

            do {
                delay(50);
                reading = _readSensor();
                attempts--;
            } while(attempts >= 0 && reading.distance.value == 0);

            return reading;          
        }

    private:

        void _pingSensor() {
            digitalWrite(TRIGGER_PIN, HIGH);
    
            digitalWrite(TRIGGER_PIN, HIGH);
            delay(100); 
            digitalWrite(TRIGGER_PIN, LOW);
            delay(4);
            digitalWrite(TRIGGER_PIN, HIGH);
        } 

        Reading _readSensor() {
            SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
            char col;
            unsigned char buffer_RTT[6] = {};
            int Rage = 0;
            float Temp = 0;
            int Tflag = 0;


            mySerial.begin(9600);
            pinMode(TRIGGER_PIN, OUTPUT);

            _pingSensor();
            _pingSensor();
         
            do{ 
                for (int j = 0; j <= 5; j++){
                    col = mySerial.read();
                    buffer_RTT[j] = (char)col;
                }      
            } while(mySerial.read() == 0xff);
            
            mySerial.flush();
            
            if(buffer_RTT[0]==0xff){
                int cor;
                cor=(buffer_RTT[0]+buffer_RTT[1]+buffer_RTT[2]+buffer_RTT[3]+buffer_RTT[4])&0x00FF;//Check
                
                if(buffer_RTT[5]==cor)
                {
                    Rage = (buffer_RTT[1] << 8) + buffer_RTT[2];
                    Tflag=  buffer_RTT[3]&0x80;
                    
                    if(Tflag==0x80){
                        buffer_RTT[3]=buffer_RTT[3]^0x80; 
                    }
                    
                    Temp = (buffer_RTT[3] << 8) + buffer_RTT[4];
                    Temp = Temp/10;
                } else {
                    Rage = 0;
                    Temp = 0;
                }
            }

            Rage = round(Rage/10);    
            
            if(VERBOSE == true) {
                _printReading(Rage, Tflag, Temp);
            }

            Reading reading;
            
            reading.distance.type = DISTANCE;
            reading.distance.units = CENTIMETERS;
            reading.distance.variable = WATER;
            reading.distance.value = Rage;

            reading.temperature.type = TEMPERATURE;
            reading.temperature.units = CELSIUS;
            reading.temperature.variable = WATER;
            reading.temperature.value = Temp;

            return reading;
        }

        void _printReading(int Rage, int Tflag, float Temp) {
                        Serial.print("Rage : ");
            Serial.print(Rage);//Output distance unit mm
            Serial.println("cm");
            Serial.print("Temperature: ");
            
            if(Tflag ==0x80) {
                Serial.print("-");           
            }
            
            Serial.print(Temp);//Output temperature
            Serial.println("℃");
            Serial.println("============================== ");
        }
};