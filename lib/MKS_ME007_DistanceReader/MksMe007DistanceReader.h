 #include <SoftwareSerial.h>

class MksMe007DistanceReader {
    public:
        struct Reading {
            int distance; // in centimeters
            float temperature;
        };

        int TRIGGER_PIN;
        int RX_PIN;
        int TX_PIN;

        MksMe007DistanceReader(int triggerPin, int rxPin, int txPin)     {
            TRIGGER_PIN = triggerPin;
            RX_PIN = rxPin;
            TX_PIN = txPin;
        }

        Reading getReading() {
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

            Reading reading;
            reading.distance = Rage;
            reading.temperature = Temp;
            digitalWrite(TRIGGER_PIN, LOW);
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
};