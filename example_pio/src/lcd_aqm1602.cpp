#include "lcd_aqm1602.h"

Aqm1602::Aqm1602(TwoWire& wire, uint8_t address) : wire_(wire), address_(address) {}

bool Aqm1602::begin() {
  delay(40);

  // ST7032/AQM1602Y recommended sequence for 3.3 V operation.
  sendCommand(0x38);
  sendCommand(0x39);
  sendCommand(0x14);
  sendCommand(0x7F);
  sendCommand(0x5E);
  sendCommand(0x6C);
  delay(200);
  sendCommand(0x38);
  sendCommand(0x0C);
  sendCommand(0x01);
  delay(2);
  sendCommand(0x06);

  return true;
}

void Aqm1602::clear() {
  sendCommand(0x01);
  delay(2);
}

void Aqm1602::home() {
  sendCommand(0x02);
  delay(2);
}

void Aqm1602::setCursor(uint8_t col, uint8_t row) {
  static constexpr uint8_t kRowOffsets[] = {0x00, 0x40};
  const uint8_t row_index = row > 1 ? 1 : row;
  sendCommand(static_cast<uint8_t>(0x80 | (kRowOffsets[row_index] + col)));
}

void Aqm1602::print(const char* text) {
  while (*text != '\0') {
    sendData(static_cast<uint8_t>(*text));
    ++text;
  }
}

void Aqm1602::sendCommand(uint8_t value) {
  writeByte(0x00, value);
}

void Aqm1602::sendData(uint8_t value) {
  writeByte(0x40, value);
}

void Aqm1602::writeByte(uint8_t control, uint8_t value) {
  wire_.beginTransmission(address_);
  wire_.write(control);
  wire_.write(value);
  wire_.endTransmission();
}
