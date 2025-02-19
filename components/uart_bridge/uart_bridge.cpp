#include "uart_bridge.h"
#include "esphome/core/log.h"
#include "USB.h"
#include "USBCDC.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";
static USBCDC USBSerial;

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
  USB.begin();
  USBSerial.begin();
  ESP_LOGD(TAG, "USB CDC initialized");
}

void UARTBridge::loop() {
  uint8_t buf[64];
  int len;

  // Handle USB to UART
  if (USBSerial.available()) {
    len = USBSerial.read(buf, sizeof(buf));
    if (len > 0) {
      ESP_LOGV(TAG, "USB->UART: %d bytes", len);
      this->uart_parent_->write_array(buf, len);
    }
  }

  // Handle UART to USB
  if (this->uart_parent_->available()) {
    len = this->uart_parent_->read_array(buf, sizeof(buf));
    if (len > 0) {
      ESP_LOGV(TAG, "UART->USB: %d bytes", len);
      USBSerial.write(buf, len);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome