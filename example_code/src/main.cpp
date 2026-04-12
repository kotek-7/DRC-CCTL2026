#include <Arduino.h>
#include <Wire.h>

#include "board_init.h"
#include "lcd_aqm1602.h"

namespace {
TwoWire LcdWire(LCD_SDA, LCD_SCL);
Aqm1602 Lcd(LcdWire);
} // namespace

void setup() {
  LcdWire.begin();
  LcdWire.setClock(100000);

  Lcd.begin();
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print("DRC-CCTL2026");
  Lcd.setCursor(0, 1);
  Lcd.print("LCD example");

  tone(BUZZER, 988, 80);   // B5
  delay(90);
  tone(BUZZER, 1319, 120); // E6
  delay(130);

  noTone(BUZZER);
}

void loop() {
}