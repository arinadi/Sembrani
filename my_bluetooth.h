// Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

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
