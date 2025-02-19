#include "uart_bridge.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart_component.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
  
  // Configure USB CDC UART (ESP32-C3's built-in USB serial)
  uart::UARTComponent::setup_usb_cdc();
}

void UARTBridge::loop() {
  uint8_t buf[64];
  size_t len;

  // Handle data from USB CDC to UART
  if ((len = uart::UARTComponent::read_usb_cdc(buf, sizeof(buf))) > 0) {
    this->uart_parent_->write_array(buf, len);
  }

  // Handle data from UART to USB CDC
  if (this->uart_parent_->available() > 0) {
    len = this->uart_parent_->read_array(buf, sizeof(buf));
    if (len > 0) {
      uart::UARTComponent::write_usb_cdc(buf, len);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome