#include "config.h" // All config
#include "pitches.h" // NOTE to INT

#include "functions.h" // Reusable code

void setup() {
  Serial.begin(115200);
  initRF();
  initBuzzer();
  feedbackTone(250, NOTE_G3);
}

void loop() {
  checkInputRF();
}
