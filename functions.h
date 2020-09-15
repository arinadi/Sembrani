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
}

void KeepAlive() {
  unsigned long KEEP_ALIVE_TIMENOW = millis(); // grab current time
  if ((unsigned long)(KEEP_ALIVE_TIMENOW - KEEP_ALIVE_LASTACTION) >= KEEP_ALIVE_TIMER) {
    startDeepSleep();
  }
}


// Bluetooth
void eventCallbackBT(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Client Connected has address:");

    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X", param->srv_open.rem_bda[i]);
      if (i < 5) {
        Serial.print(":");
      }
    }
  }

  if (event == ESP_SPP_CLOSE_EVT ) {
    Serial.println("Client disconnected");
  }
}

void initBT(String device = BT_NAME) {
  SerialBT.register_callback(eventCallbackBT);
  if (!SerialBT.begin(device)) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
}


void inputCheckBT() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    SerialBT.flush(); // clear buffer data
    SerialBT.println("OK");
    delay(200);
  }
}


// Buzzer
void initBuzzer(int channel = BUZZER_CHANNEL, int pin = BUZZER_PIN) {
  ledcSetup(channel, 8000, 4);
  ledcAttachPin(pin, channel);
}

void feedbackTone(int duration, int note = NOTE_C7) {
  // tone(34, notes[0], 25); // PIN, NOTE, DURATION
  Serial.print("note : ");
  Serial.println(note);
  ledcWriteTone(BUZZER_CHANNEL, note); //PWM CHANNEL
  delay(duration); // DURATION - ms
  ledcWrite(0, 0);
  delay(100); // SILENT - ms
}


// RF Remote
// Interrupts
void IRAM_ATTR isr() {
  RF_VT_STATE = 1;
}
void initRF() {
  pinMode(RF_VT_PIN, INPUT);
  attachInterrupt(RF_VT_PIN, isr, RISING); //Interrupts

  pinMode(RF_D0_PIN, INPUT);
  pinMode(RF_D1_PIN, INPUT);
  pinMode(RF_D2_PIN, INPUT);
  pinMode(RF_D3_PIN, INPUT);
}

void inputRegulatorRF(int type, int fbTone = NOTE_A6) {
  if (RF_CLICK == 0 && RF_CLICK_TYPE == 0) { // Single click
    RF_CLICK_TIMESTART = millis();
    RF_CLICK_TIMELIMIT = RF_CLICK_TIMESTART + RF_CLICK_TIMER;
    RF_CLICK = 1;
    RF_CLICK_TYPE = type;
    feedbackTone(300, fbTone);
  }
  else if (RF_CLICK_TYPE == type && millis() < RF_CLICK_TIMELIMIT) { // Multiple Click
    if (RF_CLICK == 1) { // Double Click
      RF_CLICK = 2;
      feedbackTone(300, fbTone);
    }
    //    else if (RF_CLICK == 2) { // Triple Click
    //      RF_CLICK = 3;
    //      feedbackTone(300, fbTone);
    //    }
  }
  Serial.print("RF_CLICK_TYPE : ");
  Serial.println(RF_CLICK_TYPE);
  Serial.print("RF_CLICK : ");
  Serial.println(RF_CLICK);
}

void inputActionRF(int type, int action = 1) {
  Serial.print("inputActionRF type : ");
  Serial.println(type);
  Serial.print("inputActionRF action : ");
  Serial.println(action);
  if (type == 1) {
    if (action == 1) {
      feedbackTone(300, NOTE_B4);
    }
    if (action == 2) {
      feedbackTone(300, NOTE_B4);
      feedbackTone(400, NOTE_B7);
    }
    if (action == 3) {
      feedbackTone(300, NOTE_B4);
      feedbackTone(400, NOTE_B7);
      feedbackTone(500, NOTE_B6);
    }
  }
  if (type == 2) {
    if (action == 1) {
      feedbackTone(300, NOTE_C8);
    }
    if (action == 2) {
      feedbackTone(300, NOTE_C8);
      feedbackTone(400, NOTE_C7);
    }
    if (action == 3) {
      feedbackTone(300, NOTE_C8);
      feedbackTone(400, NOTE_C7);
      feedbackTone(500, NOTE_C6);
    }
  }
  if (type == 3) {
    if (action == 1) {
      feedbackTone(300, NOTE_D8);
    }
    if (action == 2) {
      feedbackTone(300, NOTE_D8);
      feedbackTone(400, NOTE_D7);
    }
    if (action == 3) {
      feedbackTone(300, NOTE_D8);
      feedbackTone(400, NOTE_D7);
      feedbackTone(500, NOTE_D6);
    }
  }
  if (type == 4) {
    if (action == 1) {
      feedbackTone(300, NOTE_E4);
    }
    if (action == 2) {
      startDeepSleep();
      feedbackTone(300, NOTE_E4);
      feedbackTone(400, NOTE_E7);
    }
    if (action == 3) {
      feedbackTone(300, NOTE_E4);
      feedbackTone(400, NOTE_E7);
      feedbackTone(500, NOTE_E6);
    }
  }
}

void inputCheckRF() {
  if (RF_VT_STATE == 1) {
    //RESET STATE
    RF_VT_STATE = 0;
    // READ STATE BOTTON
    RF_D0_STATE = digitalRead(RF_D0_PIN);
    RF_D1_STATE = digitalRead(RF_D1_PIN);
    RF_D2_STATE = digitalRead(RF_D2_PIN);
    RF_D3_STATE = digitalRead(RF_D3_PIN);

    Serial.print("RF_VT_STATE : ");
    Serial.println(RF_VT_STATE);

    if (RF_D0_STATE == 1) {
      Serial.print("RF_D0_STATE : ");
      Serial.println(RF_D0_STATE);
      inputRegulatorRF(1, NOTE_B7);
    }

    if (RF_D1_STATE == 1) {
      Serial.print("RF_D1_STATE : ");
      Serial.println(RF_D1_STATE);
      inputRegulatorRF(2, NOTE_C7);
    }

    if (RF_D2_STATE == 1) {
      Serial.print("RF_D2_STATE : ");
      Serial.println(RF_D2_STATE);
      inputRegulatorRF(3, NOTE_D7);
    }

    if (RF_D3_STATE == 1) {
      Serial.print("RF_D3_STATE : ");
      Serial.println(RF_D3_STATE);
      inputRegulatorRF(4, NOTE_E7);
    }
  }
}

void inputResetRF() {
  RF_CLICK = 0;
  RF_CLICK_TYPE = 0;
  RF_CLICK_TIMESTART = 0;
  RF_CLICK_TIMELIMIT = 0;
}
