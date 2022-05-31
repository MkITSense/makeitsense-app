#ifndef MksDisplay_h
#define MksDisplay_h

#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;    // OLED display width, in pixels
const int SCREEN_HEIGHT = 32;    // OLED display height, in pixels
const int OLED_RESET = -1;       // Reset pin # (or -1 if sharing Arduino reset pin)
const int SCREEN_ADDRESS = 0x3C; ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 _Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class MksDisplay {
    public:
        void start() {
            if (!_Display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
                Serial.println(F("SSD1306 allocation failed"));
            }
        
            _progressBarPos = 0;
            _showWelcome();
        }
    
        void clear() {
            _Display.clearDisplay();
            _Display.setTextSize(1);
            _Display.setTextColor(SSD1306_WHITE);
        }
    
        void print(String message, int line, int fontSize) {
            _Display.setTextSize(fontSize);
            _Display.setTextColor(SSD1306_WHITE);
            _Display.setCursor(0, (line - 1) * 8);
            _Display.println(message);
        }
    
        void show() {
            _Display.display();
        }
    
        void updateProgressBar() {
            _Display.drawPixel(_Display.width() - 1, _progressBarPos, 0);
        
            _progressBarPos++;
        
            if (_progressBarPos > _Display.height()) {
                _progressBarPos = 0;
            }
        
            _Display.drawPixel(_Display.width() - 1, _progressBarPos, 1);
        }

    private:

        int _progressBarPos;
    
        void _showWelcome() {
            _Display.clearDisplay();
            print("MakeItSense", 1, 1);
            print("Green Flower", 2, 1);
            print("v 1.0", 3, 1);
            _Display.display();
            delay(1500);
            _Display.clearDisplay();
        }
        
};

#endif