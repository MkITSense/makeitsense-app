#include "Arduino.h"
#include "MKS_Clock.h"

MKS_Clock::MKS_Clock()
{
  stop();
}

void MKS_Clock::start()
{
  _state = STARTED;
  _startMilSec = millis();
}

void MKS_Clock::stop()
{
  _state = STOPED;
}

void MKS_Clock::pause()
{
  _state = PAUSED;
}

void MKS_Clock::resume()
{
  _state = STARTED;
}

bool MKS_Clock::isStoped()
{
  if (_state == STOPED)
  {
    return true;
  }

  return false;
}

bool MKS_Clock::isStarted()
{
  return _state == STARTED;
}

float MKS_Clock::getMinutes()
{
  if (isStoped() == false)
  {
    _currentMinutes = millis();
  }

  return (_currentMinutes - _startMilSec) / 60000;
}

float MKS_Clock::getSeconds()
{
  if (isStoped() == false)
  {
    _currentMinutes = millis();
  }

  return (_currentMinutes - _startMilSec) / 1000;
}

String MKS_Clock::getCurrentTime()
{
  if (isStoped() == false)
  {
    _currentTime = millis();
  }

  long miliseconds = _currentTime - _startMilSec;

  int seconds = (int)(miliseconds / 1000) % 60;
  int minutes = (int)((miliseconds / (1000 * 60)) % 60);
  int hours = (int)((miliseconds / (1000 * 60 * 60)) % 24);

  return MKS_Clock::_formatNumber(hours) + ":" + MKS_Clock::_formatNumber(minutes) + ":" + MKS_Clock::_formatNumber(seconds);
}

String MKS_Clock::_formatNumber(int number)
{
  char result[2];
  sprintf(result, "%02d", number);

  return String(result);
}