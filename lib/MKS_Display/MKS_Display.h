#ifndef MKS_Display_h
#define MKS_Display_h

#include "Arduino.h"
#include <Adafruit_SSD1306.h>

class MKS_Display
{
public:
  void start();
  void clear();
  void print(String message, int line, int fontSize);
  void show();
  void updateProgressBar();

private:
  int _progressBarPos;
  void _showWelcome();
};

#endif