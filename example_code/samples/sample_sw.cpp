#include <Arduino.h>

#include "board_init.h"

void setup() {
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
}

bool sw1_state = false;
bool sw2_state = false;
bool sw3_state = false;

void loop() {
  sw1_state = digitalRead(SW1) == LOW;
  sw2_state = digitalRead(SW2) == LOW;
  sw3_state = digitalRead(SW3) == LOW;
  delay(200);
}
