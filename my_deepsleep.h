//Deep Sleep
void startDeepSleep() {
  Serial.println("Go to sleep now");
  esp_deep_sleep_start();
}

void printWakeupReason() {
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : Serial.println("Wakeup caused by touchpad"); break;
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }
  feedbackTone(500, NOTE_G6);
}

void initDeepSleepWakeUp() {
  //Print the wakeup reason for ESP32
  printWakeupReason();
  //Configure GPIO12 as ext0 wake up source for HIGH logic level
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, 1);
}

void KeepAlive() {
  unsigned long KEEP_ALIVE_TIMENOW = millis(); // grab current time
  if ((unsigned long)(KEEP_ALIVE_TIMENOW - KEEP_ALIVE_LASTACTION) >= KEEP_ALIVE_TIMER) {
    startDeepSleep();
  }
}
