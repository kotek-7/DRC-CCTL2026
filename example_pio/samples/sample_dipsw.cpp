#include <Arduino.h>

#include "board_init.h"

void setup() {
  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);
}

void loop() {
  const uint8_t value =
      ((digitalRead(DIP1) == LOW) ? 0x01 : 0x00) |
      ((digitalRead(DIP2) == LOW) ? 0x02 : 0x00) |
      ((digitalRead(DIP3) == LOW) ? 0x04 : 0x00) |
      ((digitalRead(DIP4) == LOW) ? 0x08 : 0x00);
  delay(200);
}
