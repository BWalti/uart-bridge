#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace uart_bridge {

class UARTBridge : public Component {
 public:
  void set_uart_parent(uart::UARTComponent *parent) { uart_parent_ = parent; }
  void setup() override;
  void loop() override;

 protected:
  uart::UARTComponent *uart_parent_{nullptr};
};

}  // namespace uart_bridge
}  // namespace esphome