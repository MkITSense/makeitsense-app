#ifndef MKS_Clock_h
#define MKS_Clock_h

#include "Arduino.h"

class MKS_Clock
{

public:
  static const int STOPED = 0;
  static const int PAUSED = 1;
  static const int STARTED = 2;
  MKS_Clock();
  void start();
  void stop();
  void pause();
  void resume();
  bool isStoped();
  bool isStarted();
  float getMinutes();
  String getCurrentTime();

private:
  long _startMilSec;
  int _state;
  float _currentTime;
  float _currentMinutes;

  String _formatNumber(int number);
};

#endif