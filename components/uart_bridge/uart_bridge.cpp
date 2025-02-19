#include "uart_bridge.h"
#include "esphome/core/log.h"
#include "driver/usb_serial_jtag.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
  
  // Initialize USB Serial JTAG driver
  usb_serial_jtag_driver_config_t config = {
    .tx_buffer_size = 256,
    .rx_buffer_size = 256,
  };
  ESP_ERROR_CHECK(usb_serial_jtag_driver_install(&config));
}

void UARTBridge::loop() {
  uint8_t buf[64];
  size_t len;

  // Handle data from USB to UART
  len = usb_serial_jtag_read_bytes(buf, sizeof(buf), 0);
  if (len > 0) {
    this->uart_parent_->write_array(buf, len);
  }

  // Handle data from UART to USB
  if (this->uart_parent_->available() > 0) {
    len = this->uart_parent_->read_array(buf, sizeof(buf));
    if (len > 0) {
      usb_serial_jtag_write_bytes(buf, len, 0);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome