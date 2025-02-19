#include "esphome.h"

class ESP32C3Passthrough : public Component {
public:
  void setup() override {
    Serial.begin(115200);
    Serial1.begin(115200);
  }

  void loop() override {
    while (Serial.available()) {
      Serial1.write(Serial.read());
    }
    while (Serial1.available()) {
      Serial.write(Serial1.read());
    }
  }
};
