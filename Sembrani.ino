#include "variables.h" // All variables
#include "functions.h" // Reusable code

void setup() {
  Serial.begin(115200);

  initBuzzer();
  initRF();
  initBT();
  initDeepSleepWakeUp();
}

void loop() {
  inputCheckRF();
  ActionRF();
  
  inputCheckBT();

  KeepAlive();
}
