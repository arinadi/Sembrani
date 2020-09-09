//Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


//Buzzer Tone
#include "pitches.h" // NOTE to INT


#include "variables.h" // All config
#include "functions.h" // Reusable code

void setup() {
  Serial.begin(115200);
  delay(500);

  // Deep Sleep
  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  //Configure GPIO12 as ext0 wake up source for HIGH logic level
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, 1);

  initRF();
  initBT();

  initBuzzer();
  feedbackTone(250, NOTE_G3);
}

void loop() {
  inputCheckRF();
  inputCheckBT();

  if (RF_CLICK > 0 && millis() > RF_CLICK_TIMELIMIT) {
    // GO ACTION
    inputActionRF(RF_CLICK_TYPE, RF_CLICK);

    // RESET INPUT
    inputResetRF();
  }
}
