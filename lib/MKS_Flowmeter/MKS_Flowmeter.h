#ifndef MKS_Flowmeter_h
#define MKS_Flowmeter_h

#include "Arduino.h"

class MKS_Flowmeter
{

public:
  volatile byte getReading(volatile byte pulseCount);
  float getFlowRate();
  float getTotalLitres();
  void reset();
  void setup(int sensorPin);

private:
  int _sensorPin;
  long _currentMillis;
  long _previousMillis;
  int _interval;
  float _calibrationFactor;
  byte _pulse1Sec;
  float _flowRate;
  unsigned long _flowMilliLitres;
  unsigned int _totalMilliLitres;
  float _flowLitres;
  float _totalLitres;
};

#endif