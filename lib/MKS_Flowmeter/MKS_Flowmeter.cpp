#include "Arduino.h"
#include "MKS_Flowmeter.h"

void MKS_Flowmeter::setup(int sensorPin) {
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT_PULLUP);
  reset();
}

void MKS_Flowmeter::reset()
{
  _currentMillis = 0;
  _previousMillis = 0;
  _interval = 1000;
  _calibrationFactor = 4.5;
  _pulse1Sec = 0;
  _flowRate = 0.0;
  _flowMilliLitres = 0;
  _totalMilliLitres = 0;
  _previousMillis = 0;
  _totalLitres = 0;
}

volatile byte MKS_Flowmeter::getReading(volatile byte pulseCount)
{
  _currentMillis = millis();
  if (_currentMillis - _previousMillis > _interval)
  {
    _pulse1Sec = pulseCount;
    pulseCount = 0;

    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    _flowRate = ((1000.0 / (millis() - _previousMillis)) * _pulse1Sec) / _calibrationFactor;
    _previousMillis = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    _flowMilliLitres = (_flowRate / 60) * 1000;
    _flowLitres = (_flowRate / 60);

    // Add the millilitres passed in this second to the cumulative total
    _totalMilliLitres += _flowMilliLitres;
    _totalLitres += _flowLitres;
  }

  return pulseCount;
}

float MKS_Flowmeter::getFlowRate()
{
  return _flowRate;
}

float MKS_Flowmeter::getTotalLitres()
{
  return _totalLitres;
}