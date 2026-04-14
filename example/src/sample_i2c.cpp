#include "main.h"

namespace {
uint8_t detected_addresses[112] = {};
uint8_t detected_count = 0;
}

extern "C" void setup(void) {
  detected_count = 0;
  for (uint8_t address = 0x08; address <= 0x77; ++address) {
    if (HAL_I2C_IsDeviceReady(&hi2c2, static_cast<uint16_t>(address << 1), 1, 10) == HAL_OK) {
      detected_addresses[detected_count++] = address;
    }
  }
}

extern "C" void loop(void) {}
