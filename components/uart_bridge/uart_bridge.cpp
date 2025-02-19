#include "uart_bridge.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
}

void UARTBridge::loop() {
  uint8_t buf[128];
  size_t len;

  // Handle data from UART
  if (this->uart_parent_->available() > 0) {
    len = this->uart_parent_->read_array(buf, sizeof(buf));
    if (len > 0) {
      ESP_LOGV(TAG, "Received %d bytes from UART", len);
      this->uart_parent_->write_array(buf, len);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome