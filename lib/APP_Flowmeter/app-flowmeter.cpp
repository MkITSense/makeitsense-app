include <MKS_Display.h>
#include <MKS_Flowmeter.h>
#include <MKS_Clock.h>
#include "Arduino.h"

const String READY = "Listo";
const String IN_PROCESS = "En proceso...";
const String WAITING = "Esperando...";
const int FLOWMETER_PIN = 4;

MKS_Clock timerFlow;
MKS_Clock timerState;
MKS_Display display;
MKS_Flowmeter flowmeter;

String state;
int flowmeterPin;
volatile int pulseCount;

void ICACHE_RAM_ATTR pulseCounter() {
  pulseCount++;
}

void updateDisplay(float flowRate, float totalLitres) {
    String title = state;
    String flow = String(flowRate) + " L/m";
    String timer = timerFlow.getCurrentTime() + " " + String(totalLitres) + " Lts";
    
    display.clear();
    display.print(title, 1, 1);
    display.print(flow, 2, 2);
    display.print(timer, 4, 1);
    display.updateProgressBar();
    display.show();
}

void setup() {
  Serial.begin(9600);
  flowmeter.setup(FLOWMETER_PIN);
  state = READY;
  pulseCount = 0;
  display.start();
  attachInterrupt(digitalPinToInterrupt(FLOWMETER_PIN), pulseCounter, FALLING);
}

void loop() {

 
  pulseCount = flowmeter.getReading(pulseCount);
  float flowRate = flowmeter.getFlowRate();
  
  if (flowRate > 0 && state == READY) {
    flowmeter.reset();
    timerFlow.start();
    state = IN_PROCESS;
    pulseCount = 0;
  }
    
  if (flowRate <= 0 && timerFlow.isStarted() && state != WAITING) {
    state = WAITING;
    timerState.start();
  }
  
  if (flowRate > 0 && timerState.isStarted()) {
    state = IN_PROCESS;
    timerState.stop();
  }
  
  if (timerState.getMinutes() > 1 && state == WAITING) {
    state = READY;
    pulseCount = 0;
    timerFlow.stop();
    timerState.stop();
  }
    
  updateDisplay(flowRate, flowmeter.getTotalLitres());

  delay(500);
}