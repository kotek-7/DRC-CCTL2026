#include <Arduino.h>
#include <Wire.h>

#include "board_init.h"

TwoWire I2cExt(I2C_EXT_SDA, I2C_EXT_SCL);

void setup() {
  I2cExt.begin();
  I2cExt.setClock(100000);

  for (uint8_t address = 0x08; address <= 0x77; ++address) {
    I2cExt.beginTransmission(address);
    I2cExt.endTransmission();
  }
}

void loop() {
}
