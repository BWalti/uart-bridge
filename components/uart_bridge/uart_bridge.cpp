#include "uart_bridge.h"
#include "esphome/core/log.h"
#include "driver/gpio.h"
#include "esp_private/usb_phy.h"

namespace esphome {
namespace uart_bridge {

static const char *TAG = "uart_bridge";

void UARTBridge::setup() {
  ESP_LOGCONFIG(TAG, "Setting up UART Bridge...");
  
  // Explicitly disable USB CDC JTAG
  usb_phy_config_t phy_config = {
    .controller = USB_PHY_CTRL_SERIAL_JTAG,
    .target = USB_PHY_TARGET_EXT,
    .d_pin = -1,
    .d_pin_func = -1,
  };
  usb_phy_disable();
  ESP_ERROR_CHECK(usb_new_phy(&phy_config));
}

void UARTBridge::loop() {
  uint8_t buf[64];
  size_t len;

  // Handle data from UART to UART
  if (this->uart_parent_->available() > 0) {
    len = this->uart_parent_->read_array(buf, sizeof(buf));
    if (len > 0) {
      this->uart_parent_->write_array(buf, len);
    }
  }
}

}  // namespace uart_bridge
}  // namespace esphome