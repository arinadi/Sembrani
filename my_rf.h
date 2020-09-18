// RF Remote
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
      RF_CLICK_TIMELIMIT = RF_CLICK_TIMELIMIT + 500;
      feedbackTone(300, fbTone);
    }
    else if (RF_CLICK == 2) { // Triple Click
      RF_CLICK = 3;
      feedbackTone(300, fbTone);
    }
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
      feedbackTone(300, NOTE_E4);
      feedbackTone(400, NOTE_E7);
      startDeepSleep();
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

void ActionRF() {
  if (RF_CLICK > 0 && millis() > RF_CLICK_TIMELIMIT) {
    unsigned long KEEP_ALIVE_LASTACTION = millis();
    // GO ACTION
    inputActionRF(RF_CLICK_TYPE, RF_CLICK);

    // RESET INPUT
    inputResetRF();
  }
}

// Interrupts
void IRAM_ATTR signalRF() {
  Serial.println("Interrupts RF_VT_PIN");
  RF_VT_STATE = 1;
}

void initRF() {
  pinMode(RF_VT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RF_VT_PIN), signalRF, RISING); //Interrupts

  pinMode(RF_D0_PIN, INPUT);
  pinMode(RF_D1_PIN, INPUT);
  pinMode(RF_D2_PIN, INPUT);
  pinMode(RF_D3_PIN, INPUT);
}
