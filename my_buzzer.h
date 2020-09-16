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
