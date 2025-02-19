#include "uart_bridge.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
}

void UARTBridge::loop() {
  // Handle data from USB to UART
  while (Serial.available()) {
    int c = Serial.read();
    if (c >= 0) {
      this->uart_parent_->write_byte(c);
    }
  }

  // Handle data from UART to USB
  while (this->uart_parent_->available()) {
    int c = this->uart_parent_->read();
    if (c >= 0) {
      Serial.write(c);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome