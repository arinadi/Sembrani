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

void initRF() {
  pinMode(RF_VT_PIN, INPUT);
  pinMode(RF_D0_PIN, INPUT);
  pinMode(RF_D1_PIN, INPUT);
  pinMode(RF_D2_PIN, INPUT);
  pinMode(RF_D3_PIN, INPUT);
}

void inputRegulator(String type, int fbTone = NOTE_A6) {
  if (RF_CLICK == 0 && RF_CLICK_TYPE == "") {
    RF_CLICK_TIMESTART = millis();
    RF_CLICK_TIMELIMIT = RF_CLICK_TIMESTART + RF_CLICK_TIMER;
    RF_CLICK = 1;
    RF_CLICK_TYPE = type;
    feedbackTone(300, fbTone);
  }
  else if (RF_CLICK == 1 && RF_CLICK_TYPE == type && millis() < RF_CLICK_TIMELIMIT) {
    RF_CLICK = 2;
    feedbackTone(300, fbTone);
  }
  Serial.print("RF_CLICK_TYPE : ");
  Serial.println(RF_CLICK_TYPE);
  Serial.print("RF_CLICK : ");
  Serial.println(RF_CLICK);
}

void inputAction(String type, int action = 1) {
  Serial.print("RF_CLICK_TYPE : ");
  Serial.println(RF_CLICK_TYPE);
  Serial.print("RF_CLICK : ");
  Serial.println(RF_CLICK);
  feedbackTone(300, NOTE_D8);
  feedbackTone(300, NOTE_D7);
  feedbackTone(300, NOTE_D6);
}

void checkInputRF() {
  RF_VT_STATE = digitalRead(RF_VT_PIN);

  RF_D0_STATE = digitalRead(RF_D0_PIN);
  RF_D1_STATE = digitalRead(RF_D1_PIN);
  RF_D2_STATE = digitalRead(RF_D2_PIN);
  RF_D3_STATE = digitalRead(RF_D3_PIN);

  if (RF_VT_STATE == 1) {
    Serial.print("RF_VT_STATE : ");
    Serial.println(RF_VT_STATE);
    if (RF_D0_STATE == 1) {
      Serial.print("RF_D0_STATE : ");
      Serial.println(RF_D0_STATE);
      inputRegulator("RF_D0", NOTE_B7);
    }
    if (RF_D1_STATE == 1) {
      Serial.print("RF_D1_STATE : ");
      Serial.println(RF_D1_STATE);
      inputRegulator("RF_D1", NOTE_C7);
    }
    if (RF_D2_STATE == 1) {
      Serial.print("RF_D2_STATE : ");
      Serial.println(RF_D2_STATE);
      inputRegulator("RF_D2", NOTE_D7);
    }
    if (RF_D3_STATE == 1) {
      Serial.print("RF_D3_STATE : ");
      Serial.println(RF_D3_STATE);
      inputRegulator("RF_D3", NOTE_E7);
    }
  }
  if (RF_CLICK > 0 && millis() > RF_CLICK_TIMELIMIT) {
    // GO ACTION
    inputAction(RF_CLICK_TYPE, RF_CLICK);

    // RESET INPUT
    RF_CLICK = 0;
    RF_CLICK_TYPE = "";
    RF_CLICK_TIMESTART = 0;
    RF_CLICK_TIMELIMIT = 0;
  }
}
